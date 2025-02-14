#include "bcc/compiler.hpp"
#include "bcc/functions.hpp"

namespace BCC
{
    u32 LineID = 0;
    std::string CurrentCompiledFunction;
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
        { ".fn" , FunctionDefinition }
    };
    const std::unordered_map<std::string, CompileFlowFuntion> DeclarationFunctions =
    {
        { ".i32", I32ConstantDeclaration },
        { ".i64", I64ConstantDeclaration },
        { ".f32", F32ConstantDeclaration },
        { ".f64", F64ConstantDeclaration },
        { ".u32", U32ConstantDeclaration },
        { ".u64", U64ConstantDeclaration },
        { ".str", StringConstantDeclaration },
        { ".fn" , FunctionDeclaration }
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
        { "dealloc", Dealloc },
        { "cmp", Cmp }
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
        PushHWord(v, w.HValue[0]);
        PushHWord(v, w.HValue[1]);
    }
    inline static void PushDWord(std::vector<u8>& v, DWord d)
    {
        PushWord(v, d.WValue[0]);
        PushWord(v, d.WValue[1]);
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
        u16 i = 0;
        u16 main_index = 0;
        for(std::string& func : FunctionNames)
        {
            PushWord(result, functions_offset);
            functions_offset += (u32)FunctionsData[func].Opcodes.size() + 2;

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
            if(LineID >= Lines.size())
                return;
            const std::string& line = Lines[LineID];
            tokens = Split(line, ' ');
        } while (LineID < Lines.size() && tokens[0][0] != '.');
    }
    void GoToFirstDefinition()
    {
        LineID = 0;
        while(LineID < Lines.size())
        {
            std::vector<std::string> tokens = Split(Lines[LineID], ' ');
            if(!tokens.empty() && tokens[0][0] == '.')
                return;
            LineID++;
        }
    }

    void I32ConstantDefinition(std::vector<std::string>& tokens)
    {
        i32 value = 0;
        try { value = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
			(void)e;
            PushError("Invalid i32 value", tokens[2]);
        }

        WordConstantsData[tokens[1]].Value =  value;
        GoToNextLine();
    }
    void I64ConstantDefinition(std::vector<std::string>& tokens)
    {
        i64 value = 0;
        try { value = std::stoll(tokens[2]); }
        catch(const std::exception& e)
        {
			(void)e;
            PushError("Invalid i64 value", tokens[2]);
        }

        DWordConstantsData[tokens[1]].Value = value;
        GoToNextLine();
    }
    void F32ConstantDefinition(std::vector<std::string>& tokens)
    {
        f32 value = 0;
        try { value = std::stof(tokens[2]); }
        catch(const std::exception& e)
        {
			(void)e;
            PushError("Invalid f32 value", tokens[2]);
            return;
        }

        WordConstantsData[tokens[1]].Value = value;
        GoToNextLine();
    }
    void F64ConstantDefinition(std::vector<std::string>& tokens)
    {
        f64 value = 0;
        try { value = std::stod(tokens[2]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid f64 value", tokens[2]);
        }

        DWordConstantsData[tokens[1]].Value = value;
        GoToNextLine();
    }
    void U32ConstantDefinition(std::vector<std::string>& tokens)
    {
        u32 value = 0;
        try { value = (u32)std::stoul(tokens[2]); }
        catch(const std::exception& e)
        {
			(void)e;
            PushError("Invalid u32 value", tokens[2]);
        }

        WordConstantsData[tokens[1]].Value = value;
        GoToNextLine();
    }
    void U64ConstantDefinition(std::vector<std::string>& tokens)
    {
        u64 value = 0;
        try { value = std::stoull(tokens[2]); }
        catch(const std::exception& e)
        {
			(void)e;
            PushError("Invalid u64 value", tokens[2]);
        }

        DWordConstantsData[tokens[1]].Value = value;
        GoToNextLine();
    }
    void StringConstantDefinition(std::vector<std::string>& tokens)
    {
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
                PushError("Invalid string value", tokens[1]);
            else
            {
                for(size_t i = pos + 1; i < end_pos; i++)
                {
                    if(line[i] == '\\') // todo : make it less nested
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

        StringConstantsData[tokens[1]].Value = std::move(value);
        GoToNextLine();
    }
    void FunctionDefinition(std::vector<std::string>& tokens)
    {
        LabelPointers.clear();
        Jumps.clear();
        GoToNextLine();

        if(tokens.size() < 4)
        {
            PushError("Too few function definition parameters", tokens[0]);
            GoToNextDefinition();
            return;
        }
        int awc = 0;
        int lwc = 0;
        try { awc = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid argument word count", tokens[2]);
            GoToNextDefinition();
            return;
        }
        try { lwc = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
			(void)e;
            PushError("Invalid local word count", tokens[3]);
            GoToNextDefinition();
            return;
        }
        if(lwc < awc)
        {
            PushError("Local word count must be greater equal than argument word count", tokens[3]);
            GoToNextDefinition();
            return;
        }

        FunctionsData[tokens[1]].ArgWordCount   = (u8)awc;
        FunctionsData[tokens[1]].LocalWordCount = (u8)lwc;
        CurrentCompiledFunction = tokens[1];

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
            std::vector<opcode>& ops = GetCurrentFunctionOpcodesList();
            ops[index_from - 2] = (opcode)offset;
            ops[index_from - 1] = (opcode)(offset >> 8);
        }
    }
    
    void I32ConstantDeclaration(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <n> found", tokens[0]);
            return;
        }
        if(WordConstantsData.contains(tokens[1]))
        {
            PushError("Word already defined", tokens[1]);
            return;
        }
        WordConstantNames.push_back(tokens[1]);
        WordConstantsData[tokens[1]] = { 0, (u16)WordConstantsData.size() };
    }
    void I64ConstantDeclaration(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <n> found", tokens[0]);
            return;
        }
        if(DWordConstantsData.contains(tokens[1]))
        {
            PushError("DWord already defined", tokens[1]);
            return;
        }
        DWordConstantNames.push_back(tokens[1]);
        DWordConstantsData[tokens[1]] = { 0, (u16)DWordConstantsData.size() };
    }
    void U32ConstantDeclaration(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <n> found", tokens[0]);
            return;
        }
        if(WordConstantsData.contains(tokens[1]))
        {
            PushError("Word already defined", tokens[1]);
            return;
        }
        WordConstantNames.push_back(tokens[1]);
        WordConstantsData[tokens[1]] = { 0, (u16)WordConstantsData.size() };
    }
    void U64ConstantDeclaration(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <n> found", tokens[0]);
            return;
        }
        if(DWordConstantsData.contains(tokens[1]))
        {
            PushError("DWord already defined", tokens[1]);
            return;
        }
        DWordConstantNames.push_back(tokens[1]);
        DWordConstantsData[tokens[1]] = { 0, (u16)DWordConstantsData.size() };
    }
    void F32ConstantDeclaration(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <n> found", tokens[0]);
            return;
        }
        if(WordConstantsData.contains(tokens[1]))
        {
            PushError("Word already defined", tokens[1]);
            return;
        }
        WordConstantNames.push_back(tokens[1]);
        WordConstantsData[tokens[1]] = { 0, (u16)WordConstantsData.size() };
    }
    void F64ConstantDeclaration(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <n> found", tokens[0]);
            return;
        }
        if(DWordConstantsData.contains(tokens[1]))
        {
            PushError("DWord already defined", tokens[1]);
            return;
        }
        DWordConstantNames.push_back(tokens[1]);
        DWordConstantsData[tokens[1]] = { 0, (u16)DWordConstantsData.size() };
    }
    void StringConstantDeclaration(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <n> found", tokens[0]);
            return;
        }
        if(StringConstantsData.contains(tokens[1]))
        {
            PushError("String already defined", tokens[1]);
            return;
        }
        StringConstantNames.push_back(tokens[1]);
        StringConstantsData[tokens[1]] = { "", (u16)StringConstantsData.size() };
    }
    void FunctionDeclaration(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <n> found", tokens[0]);
            return;
        }
        if(FunctionsData.contains(tokens[1]))
        {
            PushError("Function already defined", tokens[1]);
            return;
        }
        FunctionNames.push_back(tokens[1]);
        FunctionsData[tokens[1]] = { (u8)0, (u8)0, (u16)FunctionsData.size(), {} };
    }

    void GoToNextLine()
    {
        std::vector<std::string> tokens;
        while(LineID < Lines.size() && tokens.size() == 0)
        {
            LineID++;
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
        LabelPointers[label] = (u16)index_from;
    }
    void AddJump(const std::string& label, size_t index_from)
    {
        if(index_from > 0xffff)
        {
            PushError("Max jump distance reached! [0, 65535]", label);
            return;
        }
        Jumps.emplace_back(label, (u16)index_from);
    }
    const std::string& CurrentFunction() { return CurrentCompiledFunction; }
    std::vector<opcode>& GetCurrentFunctionOpcodesList()
    {
        return FunctionsData[CurrentCompiledFunction].Opcodes;
    }

    bool ExistFunction(const std::string& name)       { return FunctionsData.contains(name);       }
    bool ExistConstantWord(const std::string& name)   { return WordConstantsData.contains(name);   }
    bool ExistConstantDWord(const std::string& name)  { return DWordConstantsData.contains(name);  }
    bool ExistConstantString(const std::string& name) { return StringConstantsData.contains(name); }

    
    u16 GetFunctionIndex(const std::string& name)    { return FunctionsData[name].Index;       }
    u16 GetConstWordIndex(const std::string& name)   { return WordConstantsData[name].Index;   } 
    u16 GetConstDWordIndex(const std::string& name)  { return DWordConstantsData[name].Index;  }
    u16 GetConstStringIndex(const std::string& name) { return StringConstantsData[name].Index; }

    void Compile(const std::string& input_path, const std::string& output_path)
    {
        Clear();
        Lines = GetLinesFromFile(input_path);
        RemoveComments(Lines);

        // TO-DO find all definitions and declare them first
        GoToFirstDefinition();
        while(LineID < Lines.size())
        {
            std::vector<std::string> tokens = Split(Lines[LineID], ' ');
            CompileFlowFuntion fn = DeclarationFunctions.at(tokens[0]);
            fn(tokens);
            GoToNextDefinition();
        }

        LineID = 0;
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