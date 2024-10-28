#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "bcc.hpp"

namespace BCC::Compiler
{
    u32 LineID = 0;
    std::vector<std::string> Lines;
    std::vector<Error> Errors;
    std::vector<std::string> WordConstantNames;
    std::vector<std::string> DWordConstantNames;
    std::vector<std::string> FunctionNames;
    std::unordered_map<std::string, WordData> WordConstantsData;
    std::unordered_map<std::string, DWordData> DWordConstantsData;
    std::unordered_map<std::string, FunctionData> FunctionsData;
    std::unordered_map<std::string, i16> LabelPointers;
    std::vector<std::pair<std::string, i16>> Jumps;

    void I32ConstantDefinition(std::vector<std::string>& tokens);
    void I64ConstantDefinition(std::vector<std::string>& tokens);
    void F32ConstantDefinition(std::vector<std::string>& tokens);
    void F64ConstantDefinition(std::vector<std::string>& tokens);
    void U32ConstantDefinition(std::vector<std::string>& tokens);
    void U64ConstantDefinition(std::vector<std::string>& tokens);
    void FunctionDefinition(std::vector<std::string>& tokens);

    std::unordered_map<std::string, CompileFlowFuntion> DefinitionFunctions
    {
        { ".i32", I32ConstantDefinition },
        { ".i64", I64ConstantDefinition },
        { ".f32", F32ConstantDefinition },
        { ".f64", F64ConstantDefinition },
        { ".u32", U32ConstantDefinition },
        { ".u64", U64ConstantDefinition },
        { ".func", FunctionDefinition }
    };

    std::unordered_map<std::string, CompileFlowFuntion> InstructionFunctions
    {
        { "push", Push },
        { "pop",  Pop  },
        { "add", Add },
        { "sub", Sub },
        { "mul", Mul },
        { "div", Div },
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
        { "inc", Inc },
        { "dec", Dec },
        { "load",  Load  },
        { "store", Store }
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
    inline void PushByte(std::vector<u8>& v, Byte b) { v.push_back(b.IValue); }
    inline void PushHWord(std::vector<u8>& v, HWord h)
    {
        PushByte(v, h.UValue);
        PushByte(v, h.UValue >> 8);
    }
    inline void PushWord(std::vector<u8>& v, Word w)
    {
        PushHWord(v, w.H.Value0);
        PushHWord(v, w.H.Value1);
    }
    inline void PushDWord(std::vector<u8>& v, DWord d)
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
        PushHWord(result, (u16)FunctionsData.size());

        for(std::string& word : WordConstantNames)
        {
            PushWord(result, WordConstantsData[word].value);
        }
        for(std::string& dword : DWordConstantNames)
        {
            PushDWord(result, DWordConstantsData[dword].value);
        }

        u32 functions_offset = 4;
        u32 i = 0;
        u16 main_index = 0;
        for(std::string& func : FunctionNames)
        {
            PushWord(result, functions_offset);
            functions_offset += FunctionsData[func].opcodes.size() + 2;

            if (func == "main")
                main_index = i;
            i++;
        }

        result.push_back(OpCodes::call);
        PushHWord(result, main_index);
        result.push_back(OpCodes::exit);

        for(std::string& func : FunctionNames)
        {
            result.push_back(FunctionsData[func].arg_size);
            result.push_back(FunctionsData[func].local_size);
            for(opcode& op : FunctionsData[func].opcodes)
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
            std::cerr << "Failed to open file: " << path << std::endl;
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
    void I32ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(WordConstantsData.contains(tokens[1]))
        {
            Errors.emplace_back("Word already defined", tokens[1], LineID);
            return;
        }
        WordConstantsData[tokens[1]] = { std::stoi(tokens[2]), (u16)WordConstantsData.size() };
        WordConstantNames.push_back(tokens[1]);
        ++LineID;
    }
    void I64ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(DWordConstantsData.contains(tokens[1]))
        {
            Errors.emplace_back("DWord already defined", tokens[1], LineID);
            return;
        }
        DWordConstantsData[tokens[1]] = { (u64)std::stoll(tokens[2]), (u16)DWordConstantsData.size() };
        DWordConstantNames.push_back(tokens[1]);
        ++LineID;
    }
    void F32ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(WordConstantsData.contains(tokens[1]))
        {
            Errors.emplace_back("Word already defined", tokens[1], LineID);
            return;
        }
        WordConstantsData[tokens[1]] = { std::stof(tokens[2]), (u16)WordConstantsData.size() };
        WordConstantNames.push_back(tokens[1]);
        ++LineID;
    }
    void F64ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(DWordConstantsData.contains(tokens[1]))
        {
            Errors.emplace_back("DWord already defined", tokens[1], LineID);
            return;
        }
        DWordConstantsData[tokens[1]] = { std::stod(tokens[2]), (u16)DWordConstantsData.size() };
        DWordConstantNames.push_back(tokens[1]);
        ++LineID;
    }
    void U32ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(WordConstantsData.contains(tokens[1]))
        {
            Errors.emplace_back("Word already defined", tokens[1], LineID);
            return;
        }
        WordConstantsData[tokens[1]] = { (u32)std::stoul(tokens[2]), (u16)WordConstantsData.size() };
        WordConstantNames.push_back(tokens[1]);
        ++LineID;
    }
    void U64ConstantDefinition(std::vector<std::string>& tokens)
    {
        if(DWordConstantsData.contains(tokens[1]))
        {
            Errors.emplace_back("DWord already defined", tokens[1], LineID);
            return;
        }
        DWordConstantsData[tokens[1]] = { (u64)std::stoull(tokens[2]), (u16)DWordConstantsData.size() };
        DWordConstantNames.push_back(tokens[1]);
        ++LineID;
    }
    void FunctionDefinition(std::vector<std::string>& tokens)
    {
        LabelPointers.clear();
        Jumps.clear();
        ++LineID;
        if(FunctionsData.contains(tokens[1]))
        {
            Errors.emplace_back("Function already defined", tokens[1], LineID);
            do
            {
                const std::string& line = Lines[LineID++];
                tokens = Split(line, ' ');
            } while (tokens[0] != "return");
            return;
        }
        if(tokens.size() < 4)
        {
            Errors.emplace_back("Too few arguments for", tokens[0], LineID);
            do
            {
                const std::string& line = Lines[LineID++];
                tokens = Split(line, ' ');
            } while (tokens[0] != "return");
            return;
        }
        FunctionsData[tokens[1]] = { (u8)std::stoi(tokens[2]), (u8)std::stoi(tokens[3]), (u16)FunctionsData.size(), {} };
        FunctionNames.push_back(tokens[1]);
        std::string curFunc = tokens[1];

        while(LineID < Lines.size())
        {
            const std::string& line = Lines[LineID];
    
            if(line == "")
            {
                ++LineID;
                continue;
            }
            
            tokens = Split(line, ' ');

            if(tokens[0][0] == '.')
                break;

            if(InstructionFunctions.contains(tokens[0]))
            {
                CompileFlowFuntion func = InstructionFunctions[tokens[0]];
                func(tokens);
            }
            else
                Errors.emplace_back("Unknown instruction", tokens[0], LineID);

            ++LineID; 
        }

        for (auto&[label, index_from] : Jumps)
        {
            i16 offset = LabelPointers[label] - index_from;
            std::vector<opcode>& ops = FunctionsData[curFunc].opcodes;
            ops[index_from - 2] = offset;
            ops[index_from - 1] = offset >> 8;
        }
        
    }
    
    void Compile(const std::string& input_path, const std::string& output_path)
    {
        Clear();
        Lines = GetLinesFromFile(input_path);

        while(LineID < Lines.size())
        {
            std::string& line = Lines[LineID];
            if(line == "")
            {
                ++LineID;
                continue;
            }
            std::vector<std::string> tokens = Split(line, ' ');
            
            if(DefinitionFunctions.contains(tokens[0]))
                DefinitionFunctions[tokens[0]](tokens);
            else
            {
                Errors.emplace_back("Invalid label", tokens[0], LineID);
                ++LineID;
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