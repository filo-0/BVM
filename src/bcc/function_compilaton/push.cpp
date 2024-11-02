#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{    
    void PushConst(std::vector<std::string>& tokens);
    void PushLocal(std::vector<std::string>& tokens);
    void PushAs(std::vector<std::string>& tokens);
    void PushRef(std::vector<std::string>& tokens);

    void PushLocalByte(std::vector<std::string>& tokens);
    void PushLocalHWord(std::vector<std::string>& tokens);
    void PushLocalWord(std::vector<std::string>& tokens);
    void PushLocalDword(std::vector<std::string>& tokens);
    void PushLocalWords(std::vector<std::string>& tokens);

    void PushAsI32(std::vector<std::string>& tokens);
    void PushAsI64(std::vector<std::string>& tokens);
    void PushAsF32(std::vector<std::string>& tokens);
    void PushAsF64(std::vector<std::string>& tokens);

    const std::unordered_map<std::string, CompileFlowFuntion> PushFunctions
    {
        { "const", PushConst },
        { "local", PushLocal },
        { "as", PushAs },
        { "ref", PushRef}
    };

    const std::unordered_map<std::string, CompileFlowFuntion> PushLocalFunctions
    {
        { "byte", PushLocalByte },
        { "hword", PushLocalHWord },
        { "word", PushLocalWord },
        { "dword", PushLocalDword },
        { "words", PushLocalWords }
    };

    const std::unordered_map<std::string, CompileFlowFuntion> PushAsFunctions
    {
        { "i32", PushAsI32 },
        { "i64", PushAsI64 },
        { "f32", PushAsF32 },
        { "f64", PushAsF64 }
    };

    void PushConst(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 4)
        {
            PushError("Invalid number of parameters {2}", tokens[0]);
            return;
        }
        if(tokens[2].compare("word") == 0)
        {
            u16 index = GetConstWordIndex(tokens[3]);
            if(index < 256)
            {
                GetCurrentFunctionOpcodesList().push_back(OpCodes::push_word_from_pool);
                GetCurrentFunctionOpcodesList().push_back(index);
            }
            else
            {
                GetCurrentFunctionOpcodesList().push_back(OpCodes::push_word_from_pool_wide);
                GetCurrentFunctionOpcodesList().push_back(index);
                GetCurrentFunctionOpcodesList().push_back(index >> 8);
            }
            
        }
        else if (tokens[2].compare("dword") == 0)
        {
            u16 index = GetConstDWordIndex(tokens[3]);
            if(index < 256)
            {
                GetCurrentFunctionOpcodesList().push_back(OpCodes::push_dword_from_pool);
                GetCurrentFunctionOpcodesList().push_back(index);
            }
            else
            {
                GetCurrentFunctionOpcodesList().push_back(OpCodes::push_dword_from_pool_wide);
                GetCurrentFunctionOpcodesList().push_back(index);
                GetCurrentFunctionOpcodesList().push_back(index >> 8);
            }
        }
        else if (tokens[2].compare("string") == 0)
        {
            u16 index = GetConstStringIndex(tokens[3]);
            if(index < 256)
            {
                GetCurrentFunctionOpcodesList().push_back(OpCodes::push_string_from_pool);
                GetCurrentFunctionOpcodesList().push_back(index);
            }
            else
            {
                GetCurrentFunctionOpcodesList().push_back(OpCodes::push_string_from_pool_wide);
                GetCurrentFunctionOpcodesList().push_back(index);
                GetCurrentFunctionOpcodesList().push_back(index >> 8);
            }
        }
        else
        {
            PushError("Invalid <t> parameter {word, dword}", tokens[2]);
        }
    }

    void PushLocalByte(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 5)
        {
            PushError("Invalid number of parameters {3}", tokens[0]);
            return;
        }
        int byte_index;
        int local_index;

        try { byte_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <b> parameter [0, 3]", tokens[3]);
        }
        try { local_index = std::stoi(tokens[4]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[4]);
        }

        if(local_index > 255 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[4]);
            return;
        }
        switch (byte_index)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_byte_0);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;    
        case 1:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_byte_1);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_byte_2);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        case 3:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_byte_3);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        default:
            PushError("Invalid <b> parameter [0, 3]", tokens[3]);
        }
    }
    void PushLocalHWord(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 5)
        {
            PushError("Invalid number of parameters {3}", tokens[0]);
            return;
        }
        int hword_index;
        int local_index;

        try { hword_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <h> parameter {0, 2}", tokens[3]);
        }
        try { local_index = std::stoi(tokens[4]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[4]);
        }

        if(local_index > 255 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[4]);
            return;
        }
        switch (hword_index)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_hword_0);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_hword_2);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        default:
            PushError("Invalid <h> parameter {0, 2}", tokens[3]);
        }
    }
    void PushLocalWord(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 4)
        {
            PushError("Invalid number of parameters {2}", tokens[0]);
            return;
        }
        int local_index;
        try { local_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[3]);
        }


        if(local_index > 255 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[3]);
            return;
        }
        switch (local_index)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_word_0);
            break;
        case 1:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_word_1);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_word_2);
            break;
        case 3:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_word_3);
            break;
        default:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_word);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        }
    }
    void PushLocalDword(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 4)
        {
            PushError("Invalid number of parameters {2}", tokens[0]);
            return;
        }
        int local_index;
        try { local_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <l> parameter [0, 254]", tokens[3]);
        }

        if(local_index > 254 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 254]", tokens[3]);
            return;
        }
        switch (local_index)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_dword_0);
            break;
        case 1:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_dword_1);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_dword_2);
            break;
        case 3:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_dword_3);
            break;
        default:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_dword);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        }
    }
    void PushLocalWords(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 5)
        {
            PushError("Invalid number of parameters {3}", tokens[0]);
            return;
        }
        int local_index;
        int count;
        try { local_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[3]);
        }
        try { count = std::stoi(tokens[4]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <n> parameter [0, 255]", tokens[4]);
        }

        if(count < 0 || count > 255)
        {
            PushError("invalid <n> parameter [0, 255]", tokens[4]);
            return;
        }
        if(local_index + count > 255 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 255 - n]", tokens[3]);
            return;
        }
        GetCurrentFunctionOpcodesList().push_back(OpCodes::push_words);
        GetCurrentFunctionOpcodesList().push_back(local_index);
        GetCurrentFunctionOpcodesList().push_back(count);
    }
    void PushLocal(std::vector<std::string>& tokens)
    {
        if(PushLocalFunctions.contains(tokens[2]))
            PushLocalFunctions.at(tokens[2])(tokens);
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword}", tokens[2]);
    }

    void PushAsI32(std::vector<std::string>& tokens)
    {
        int value;
        try { value = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <v> parameter [-128, 127]", tokens[3]);
        }

        if(value > 127 || value < -128)
        {
            PushError("Invalid <v> parameter [-128, 127]", tokens[3]);
            return;
        }
        switch (value)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_word_value_0);
            break;
        case 1:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_i32_1);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_i32_2);
            break;
        default:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_i8_as_i32);
            GetCurrentFunctionOpcodesList().push_back(value);
            break;
        }      
    }
    void PushAsI64(std::vector<std::string>& tokens)
    {
        int value;
        try { value = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <v> parameter [-128, 127]", tokens[3]);
        }

        if(value > 127 || value < -128)
        {
            PushError("Invalid <v> parameter [-128, 127]", tokens[3]);
            return;
        }
        switch (value)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_dword_value_0);
            break;
        case 1:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_i64_1);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_i64_2);
            break;
        default:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_i8_as_i64);
            GetCurrentFunctionOpcodesList().push_back(value);
            break;
        }
    }
    void PushAsF32(std::vector<std::string>& tokens)
    {
        int value;
        try { value = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <v> parameter {0, 1, 2}", tokens[3]);
        }

        switch (value)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_word_value_0);
            break;
        case 1:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_f32_1);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_f32_2);
            break;
        default:
            PushError("Invalid <v> parameter {0, 1, 2}", tokens[3]);
            break;
        }
    }
    void PushAsF64(std::vector<std::string>& tokens)
    {
        int value;
        try { value = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <v> parameter {0, 1, 2}", tokens[3]);
        }
        switch (value)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_dword_value_0);
            break;
        case 1:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_f64_1);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::push_f64_2);
            break;
        default:
            PushError("Invalid <v> parameter {0, 1, 2}", tokens[3]);    
            break;
        }
    }
    void PushAs(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 4)
        {
            PushError("Invalid number of parameters {2}", tokens[0]);
            return;
        }
        if(PushAsFunctions.contains(tokens[2]))
            PushAsFunctions.at(tokens[2])(tokens);
        else
            PushError("Invalid <t> parameter {i32, i64, f32, f64}", tokens[2]);
    }

    void PushRef(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 4)
        {
            PushError("Invalid number of parameters {2}", tokens[0]);
            return;
        }
        int local;
        try { local = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[2]);
        }

        if(local < 0 || local > 255)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[1]);
            return;
        }
        std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::get_address);
        opcodes.push_back(local);
    }

    void Push(std::vector<std::string>& tokens)
    {
        if(PushFunctions.contains(tokens[1]))
            PushFunctions.at(tokens[1])(tokens);
        else
            PushError("Invalid variant {local, cons, as, ref}", tokens[1]);
    }
}