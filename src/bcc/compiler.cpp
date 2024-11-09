#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "bcc.hpp"

namespace BCC::Compiler
{
    u32 LineID = 0;
    std::vector<std::string> Lines;
    std::vector<Error> Errors;
    std::vector<std::string> WordConstantNames;
    std::vector<std::string> DWordConstantNames;
    std::vector<std::string> StringConstantNames;
    std::vector<std::string> FunctionNames;
    std::unordered_map<std::string, WordData> WordConstantsData;
    std::unordered_map<std::string, DWordData> DWordConstantsData;
    std::unordered_map<std::string, StringData> StringConstantsData;
    std::unordered_map<std::string, FunctionData> FunctionsData;
    std::unordered_map<std::string, u16> LabelPointers;
    std::vector<std::pair<std::string, u16>> Jumps;

    const std::unordered_map<std::string, CompileFlowFuntion> DefinitionFunctions =
    {
        { ".i32", I32ConstantDefinition },
        { ".i64", I64ConstantDefinition },
        { ".f32", F32ConstantDefinition },
        { ".f64", F64ConstantDefinition },
        { ".u32", U32ConstantDefinition },
        { ".u64", U64ConstantDefinition },
        { ".str", StringConstantDefinition },
        { ".func", FunctionDefinition }
    };
    const std::unordered_map<std::string, CompileFlowFuntion> InstructionFunctions =
    {
        { "push", Push },
        { "pop",  Pop  },
        { "add", Add },
        { "sub", Sub },
        { "mul", Mul },
        { "div", Div },
        { "neg", Neg },
        { "inc", Inc },
        { "dec", Dec },
        { "and", And },
        { "or",  Or    },
        { "xor", Xor   },
        { "not", Not   },
        { "shl", Shl   },
        { "shr", Shr   },
        { "cast", Cast },
        { "syscall", Syscall },
        { "return", Return   },
        { "call", Call },
        { "jump", Jump },
        { "dup",  Dup  },
        { "swap", Swap },
        { "label", Label },
        { "load",  Load  },
        { "store", Store },
        { "alloc", Alloc },
        { "dealloc", Dealloc }
    };

    std::vector<std::string> Split(const std::string& text, char delimiter)
    {
        std::vector<std::string> result;
        u32 i = 0;
        u32 j = 0;
        while(i < text.length())
        {
            while(j < text.length() && text[j] != delimiter)
                j++;

            if(j != i) 
                result.push_back(text.substr(i, j - i));
            i = ++j;
        }
        return result;
    }
   
    inline static void PushByte(std::vector<u8>& v, Byte b) { v.push_back(b.IValue); }
    inline static void PushHWord(std::vector<u8>& v, HWord h)
    {
        PushByte(v, h.UValue);
        PushByte(v, h.UValue >> 8);
    }
    inline static void PushWord(std::vector<u8>& v, Word w)
    {
        PushHWord(v, w.H.Value0);
        PushHWord(v, w.H.Value1);
    }
    inline static void PushDWord(std::vector<u8>& v, DWord d)
    {
        PushWord(v, d.W.Value0);
        PushWord(v, d.W.Value1);
    }

    void Clear()
    {
        WordConstantNames.clear();
        DWordConstantNames.clear();
        FunctionNames.clear();
        WordConstantsData.clear();
        DWordConstantsData.clear();
        FunctionsData.clear();
        Lines.clear();
        Errors.clear();
        LineID = 0;
    }
    
    std::vector<opcode> BuildBytecode()
    {
        std::vector<opcode> result;
        PushHWord(result, (u16)WordConstantsData.size());
        PushHWord(result, (u16)DWordConstantsData.size());
        PushHWord(result, (u16)StringConstantsData.size());
        PushHWord(result, (u16)FunctionsData.size());

        for(std::string& word : WordConstantNames)
            PushWord(result, WordConstantsData[word].Value);
        for(std::string& dword : DWordConstantNames)
            PushDWord(result, DWordConstantsData[dword].Value);
        for(std::string& str : StringConstantNames)
        {
            for(char c : StringConstantsData[str].Value)
                result.push_back(c);
            result.push_back('\0');
        }

        u32 functions_offset = 4;
        u32 i = 0;
        u16 main_index = 0;
        for(std::string& func : FunctionNames)
        {
            PushWord(result, functions_offset);
            functions_offset += FunctionsData[func].Opcodes.size() + 2;

            if (func == "main")
                main_index = i;
            i++;
        }

        result.push_back(OpCodes::call);
        PushHWord(result, main_index);
        result.push_back(OpCodes::exit);

        for(std::string& func : FunctionNames)
        {
            result.push_back(FunctionsData[func].ArgWordCount);
            result.push_back(FunctionsData[func].LocalWordCount);
            for(opcode& op : FunctionsData[func].Opcodes)
                result.push_back(op);
        }
        return result;
    }
    std::vector<std::string> GetLinesFromFile(const std::string& path)
    {
        std::vector<std::string> result;
        std::fstream file(path);
        if(!file.is_open())
        {
            PushError("Failed to open file", path);
            return result;
        }

        std::string line;
        while(std::getline(file, line))
            result.push_back(line);

        file.close();
        return result;
    } 
    void ConvertBytecodeToFile(const std::vector<opcode>& bytecode, const std::string& path)
    {
        std::fstream file(path, std::ios::out | std::ios::binary);
        if(!file.is_open())
        {
            std::cerr << "Failed to open file: " << path << std::endl;
            return;
        }

        for(opcode op : bytecode)
            file.write((char*)&op, sizeof(opcode));
        
        file.close();
    }
    void RemoveComments(std::vector<std::string>& lines)
    {
        for(std::string& line : lines)
        {
            size_t comment_pos = line.find('#');
            if(comment_pos != std::string::npos)
                line = line.substr(0, comment_pos);       
        }
    }

    void GoToNextDefinition()
    {
        std::vector<std::string> tokens;
        do
        {
            GoToNextLine();
            const std::string& line = Lines[LineID];
            tokens = Split(line, ' ');
        } while (LineID < Lines.size() && tokens[0][0] != '.');
    }
    void I32ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(WordConstantsData.contains(tokens[1]))
            PushError("Word already defined", tokens[1]);

        i32 value;
        try { value = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid i32 value", tokens[2]);
        }

        size_t index = WordConstantsData.size();
        if(index > 0xffff)
            PushError("Max constant count reached! [0, 65535]", tokens[1]);
        WordConstantsData[tokens[1]] = { value, (u16) index};
        WordConstantNames.push_back(tokens[1]);
        GoToNextLine();
    }
    void I64ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(DWordConstantsData.contains(tokens[1]))
            PushError("DWord already defined", tokens[1]);

        i64 value;
        try { value = std::stoll(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid i64 value", tokens[2]);
        }

        size_t index = DWordConstantsData.size();
        if(index > 0xffff)
            PushError("Max constant count reached! [0, 65535]", tokens[1]);
        DWordConstantsData[tokens[1]] = { value, (u16)index };
        DWordConstantNames.push_back(tokens[1]);
        GoToNextLine();
    }
    void F32ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(WordConstantsData.contains(tokens[1]))
            PushError("Word already defined", tokens[1]);

        f32 value;
        try { value = std::stof(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid f32 value", tokens[2]);
            return;
        }
        size_t index = WordConstantsData.size();
        if(index > 0xffff)
            PushError("Max constant count reached! [0, 65535]", tokens[1]);

        WordConstantsData[tokens[1]] = { value, (u16)index };
        WordConstantNames.push_back(tokens[1]);
        GoToNextLine();
    }
    void F64ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(DWordConstantsData.contains(tokens[1]))
            PushError("DWord already defined", tokens[1]);

        f64 value;
        try { value = std::stod(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid f64 value", tokens[2]);
        }

        size_t index = DWordConstantsData.size();
        if(index > 0xffff)
            PushError("Max constant count reached! [0, 65535]", tokens[1]);

        DWordConstantsData[tokens[1]] = { value, (u16)index };
        DWordConstantNames.push_back(tokens[1]);
        GoToNextLine();
    }
    void U32ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(WordConstantsData.contains(tokens[1]))
            PushError("Word already defined", tokens[1]);

        u32 value;
        try { value = std::stoul(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid u32 value", tokens[2]);
        }
        
        size_t index = WordConstantsData.size();
        if(index > 0xffff)
            PushError("Max constant count reached! [0, 65535]", tokens[1]);

        WordConstantsData[tokens[1]] = { value, (u16)index };
        WordConstantNames.push_back(tokens[1]);
        GoToNextLine();
    }
    void U64ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(DWordConstantsData.contains(tokens[1]))
            PushError("DWord already defined", tokens[1]);

        u64 value;
        try { value = std::stoull(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid u64 value", tokens[2]);
        }

        size_t index = DWordConstantsData.size();
        if(index > 0xffff)
            PushError("Max constant count reached! [0, 65535]", tokens[1]);

        DWordConstantsData[tokens[1]] = { value, (u16)index };
        DWordConstantNames.push_back(tokens[1]);
        GoToNextLine();
    }
    void StringConstantDefinition(std::vector<std::string>& tokens)
    {
        if(StringConstantsData.contains(tokens[1]))
            PushError("String already defined", tokens[1]);

        std::string value;
        std::string line = Lines[LineID];
        size_t pos = line.find_first_of('"');
        if(pos == std::string::npos)
        {
            PushError("Invalid string value", tokens[1]);
        }
        else{
            size_t end_pos = line.find_last_of('"');
            if(end_pos == std::string::npos)
            {
                PushError("Invalid string value", tokens[1]);
            }
            else
            {
                for(size_t i = pos + 1; i < end_pos; i++)
                {
                    if(line[i] == '\\')
                    {
                        if(i + 1 < end_pos)
                        {
                            switch(line[i + 1])
                            {
                                case 'n': value.push_back('\n'); break;
                                case 't': value.push_back('\t'); break;
                                case 'r': value.push_back('\r'); break;
                                case '\\': value.push_back('\\'); break;
                                case '"': value.push_back('"'); break;
                                default: PushError("Invalid escape sequence", tokens[1]);
                            }
                            i++;
                        }
                        else
                        {
                            PushError("Invalid escape sequence", tokens[1]);
                        }
                    }
                    else
                    {
                        value.push_back(line[i]);
                    }
                }
            }
        }
        

        size_t index = StringConstantsData.size();
        if(index > 0xffff)
            PushError("Max constant count reached! [0, 65535]", tokens[1]);

        StringConstantsData[tokens[1]] = { std::move(value), (u16)index };
        StringConstantNames.push_back(tokens[1]);
        GoToNextLine();
    }
    
    void FunctionDefinition(std::vector<std::string>& tokens)
    {
        LabelPointers.clear();
        Jumps.clear();
        GoToNextLine();
        if(FunctionsData.contains(tokens[1]))
        {
            PushError("Function already defined", tokens[1]);
            GoToNextDefinition();
            return;
        }
        if(tokens.size() < 4)
        {
            PushError("Too few arguments for", tokens[0]);
            GoToNextDefinition();
            return;
        }
        int awc, lwc;
        try { awc = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid argument word count", tokens[2]);
            GoToNextDefinition();
            return;
        }
        try { lwc = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid local word count", tokens[3]);
            GoToNextDefinition();
            return;
        }

        FunctionsData[tokens[1]] = { (u8)awc, (u8)lwc, (u16)FunctionsData.size(), {} };
        FunctionNames.push_back(tokens[1]);
        std::string curFunc = tokens[1];

        while(LineID < Lines.size())
        {
            const std::string& line = Lines[LineID];
            tokens = Split(line, ' ');

            if(tokens[0][0] == '.')
                break;

            if(InstructionFunctions.contains(tokens[0]))
            {
                CompileFlowFuntion func = InstructionFunctions.at(tokens[0]);
                func(tokens);
            }
            else
                PushError("Unknown instruction", tokens[0]);

            GoToNextLine(); 
        }

        for (auto&[label, index_from] : Jumps)
        {
            int label_pointer = LabelPointers[label];
            int jump_index_from = index_from;
            int offset = (label_pointer - jump_index_from);
            if(offset > 0x7fff || offset < -0x8000)
            {
                PushError("Max jump distance reached! [-32768, 32767]", label);
            }
            std::vector<opcode>& ops = FunctionsData[curFunc].Opcodes;
            ops[index_from - 2] = offset;
            ops[index_from - 1] = offset >> 8;
        }
    }
    
    void GoToNextLine()
    {
        std::vector<std::string> tokens;
        while(LineID < Lines.size() && tokens.size() == 0)
        {
            ++LineID;
            if(LineID >= Lines.size())
                return;
            tokens = Split(Lines[LineID], ' ');
        }
    }
    void PushError(const std::string& msg, const std::string& token)
    {
        Errors.emplace_back(msg, token, LineID + 1);
    }
    void AddLabelPointer(const std::string& label, size_t index_from)
    {
        if(LabelPointers.contains(label))
        {
            PushError("Label already defined", label);
            return;
        }
        if(index_from > 0xffff)
            {
                PushError("Max jump distance reached! [0, 65535]", label);
                return;
            }
        LabelPointers[label] = index_from;
    }
    void AddJump(const std::string& label, size_t index_from)
    {
        if(index_from > 0xffff)
        {
            PushError("Max jump distance reached! [0, 65535]", label);
            return;
        }
        Jumps.emplace_back(label, index_from);
    }
    std::vector<opcode>& GetCurrentFunctionOpcodesList()
    {
        return FunctionsData[FunctionNames.back()].Opcodes;
    }

    bool ExistFunction(const std::string& name)
    {
        return FunctionsData.contains(name);
    }
    u16 GetFunctionIndex(const std::string& name) { return FunctionsData[name].Index; }
    u16 GetConstWordIndex(const std::string& name) { return WordConstantsData[name].Index; }
    u16 GetConstDWordIndex(const std::string& name) { return DWordConstantsData[name].Index; }
    u16 GetConstStringIndex(const std::string& name) { return StringConstantsData[name].Index; }

    void Compile(const std::string& input_path, const std::string& output_path)
    {
        Clear();
        Lines = GetLinesFromFile(input_path);
        RemoveComments(Lines);

        while(LineID < Lines.size())
        {
            std::string& line = Lines[LineID];
            if(line == "")
            {
                GoToNextLine();
                continue;
            }
            std::vector<std::string> tokens = Split(line, ' ');
            
            if(DefinitionFunctions.contains(tokens[0]))
            {
                CompileFlowFuntion f = DefinitionFunctions.at(tokens[0]);
                f(tokens);
            }
            else
            {
                PushError("Invalid label", tokens[0]);
                GoToNextLine();
            }
        }

        if(Errors.empty())
        {
            std::vector<opcode> bytecode = BuildBytecode();
            ConvertBytecodeToFile(bytecode, output_path);
            std::cout << "Compilation successful!" << std::endl;
        }
        else
        {
            for(const Error& err : Errors)
                std::cerr << err.msg << " for token \"" << err.token << "\" at line " << err.line << std::endl;
        }
    }
} // namespace BCC