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
        if(tokens[2].compare("word") == 0)
        {
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_word_from_pool);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(WordConstantsData[tokens[3]].Index);
        }
        else if (tokens[2].compare("dword") == 0)
        {
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_dword_from_pool);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(DWordConstantsData[tokens[3]].Index);
        }
        else
        {
            Errors.emplace_back("Invalid push const specifier", tokens[2], LineID);
        }
    }

    void PushLocalByte(std::vector<std::string>& tokens)
    {
        int byte_index;
        int local_index;

        try { byte_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid byte index", tokens[3], LineID);
        }
        try { local_index = std::stoi(tokens[4]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid local index", tokens[4], LineID);
        }

        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index", tokens[4], LineID);
            return;
        }
        switch (byte_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_byte_0);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;    
        case 1:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_byte_1);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_byte_2);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_byte_3);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        default:
            Errors.emplace_back("Invalid byte index", tokens[3], LineID);
        }
    }
    void PushLocalHWord(std::vector<std::string>& tokens)
    {
        int hword_index;
        int local_index;

        try { hword_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid hword index", tokens[3], LineID);
        }
        try { local_index = std::stoi(tokens[4]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid local index", tokens[4], LineID);
        }

        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index", tokens[4], LineID);
            return;
        }
        switch (hword_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_hword_0);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_hword_2);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        default:
            Errors.emplace_back("Invalid hword index", tokens[3], LineID);
        }
    }
    void PushLocalWord(std::vector<std::string>& tokens)
    {
        int local_index;
        try { local_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid local index", tokens[3], LineID);
        }


        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index", tokens[3], LineID);
            return;
        }
        switch (local_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_word_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_word_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_word_2);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_word_3);
            break;
        default:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_word);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        }
    }
    void PushLocalDword(std::vector<std::string>& tokens)
    {
        int local_index;
        try { local_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid local index", tokens[3], LineID);
        }

        if(local_index > 254 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index", tokens[3], LineID);
            return;
        }
        switch (local_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_dword_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_dword_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_dword_2);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_dword_3);
            break;
        default:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_dword);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        }
    }
    void PushLocalWords(std::vector<std::string>& tokens)
    {
        int local_index;
        int count;
        try { local_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid local index", tokens[3], LineID);
        }
        try { count = std::stoi(tokens[4]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid push words count", tokens[4], LineID);
        }

        if(count < 0 || count > 255)
        {
            Errors.emplace_back("invalid push words count", tokens[4], LineID);
            return;
        }
        if(local_index + count > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index", tokens[3], LineID);
            return;
        }
        FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_words);
        FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
        FunctionsData[FunctionNames.back()].Opcodes.push_back(count);
    }
    void PushLocal(std::vector<std::string>& tokens)
    {
        if(PushLocalFunctions.contains(tokens[2]))
            PushLocalFunctions.at(tokens[2])(tokens);
        else
            Errors.emplace_back("Invalid bush local type", tokens[2], LineID);
    }

    void PushAsI32(std::vector<std::string>& tokens)
    {
        int value;
        try { value = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid value", tokens[3], LineID);
        }

        if(value > 127 || value < -128)
        {
            Errors.emplace_back("Invalid value [-128, 127]", tokens[3], LineID);
            return;
        }
        switch (value)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_word_value_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_i32_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_i32_2);
            break;
        default:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_i8_as_i32);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(value);
            break;
        }      
    }
    void PushAsI64(std::vector<std::string>& tokens)
    {
        int value;
        try { value = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid value", tokens[3], LineID);
        }

        if(value > 127 || value < -128)
        {
            Errors.emplace_back("Invalid value [-128, 127]", tokens[3], LineID);
            return;
        }
        switch (value)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_dword_value_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_i64_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_i64_2);
            break;
        default:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_i8_as_i64);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(value);
            break;
        }
    }
    void PushAsF32(std::vector<std::string>& tokens)
    {
        int value;
        try { value = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid value", tokens[3], LineID);
        }

        switch (value)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_word_value_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_f32_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_f32_2);
            break;
        default:
            Errors.emplace_back("Value out of range {0, 1, 2}", tokens[3], LineID);
            break;
        }
    }
    void PushAsF64(std::vector<std::string>& tokens)
    {
        int value;
        try { value = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid value", tokens[3], LineID);
        }
        switch (value)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_dword_value_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_f64_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::push_f64_2);
            break;
        default:
            Errors.emplace_back("Value out of range {0, 1, 2}", tokens[3], LineID);    
            break;
        }
    }
    void PushAs(std::vector<std::string>& tokens)
    {
        if(PushAsFunctions.contains(tokens[2]))
            PushAsFunctions.at(tokens[2])(tokens);
        else
            Errors.emplace_back("Invalid push as type", tokens[2], LineID);
    }

    void PushRef(std::vector<std::string>& tokens)
    {
        int local;
        try { local = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid local index [0, 255]", tokens[2], LineID);
        }

        if(local < 0 || local > 255)
        {
            Errors.emplace_back("Invalid local index [0, 255]", tokens[1], LineID);
            return;
        }
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].Opcodes;
        opcodes.push_back(OpCodes::get_address);
        opcodes.push_back(local);
    }

    void Push(std::vector<std::string>& tokens)
    {
        if(PushFunctions.contains(tokens[1]))
            PushFunctions.at(tokens[1])(tokens);
        else
            Errors.emplace_back("Invalid push specifier", tokens[1], LineID);
    }
}