#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    void PopByte(std::vector<std::string>& tokens);
    void PopHWord(std::vector<std::string>& tokens);
    void PopWord(std::vector<std::string>& tokens); 
    void PopDWord(std::vector<std::string>& tokens);
    void PopWords(std::vector<std::string>& tokens);

    inline const std::unordered_map<std::string, CompileFlowFuntion> PopFunctions
    {
        { "byte",  PopByte  },
        { "hword", PopHWord },
        { "word",  PopWord  },
        { "dword", PopDWord },
        { "words", PopWords }
    };

    void PopByte(std::vector<std::string>& tokens)
    {
        int byte_index;
        int local_index;

        try { byte_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid byte index", tokens[2], LineID);
        }
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
        switch (byte_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_byte_0);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;    
        case 1:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_byte_1);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_byte_2);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_byte_3);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        default:
            Errors.emplace_back("Invalid byte index", tokens[2], LineID);
            return;
        }
    }
    void PopHWord(std::vector<std::string>& tokens)
    {
        int hword_index;
        int local_index;
        try { hword_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid hword index [0, 2]", tokens[2], LineID);
        }
        try { local_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid local index [0, 255]", tokens[3], LineID);
        }

        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index [0, 255]", tokens[3], LineID);
            return;
        }
        switch (hword_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_hword_0);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_hword_2);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        default:
            Errors.emplace_back("Invalid hword index [0, 255]", tokens[2], LineID);
            return;
        }
    }
    void PopWord(std::vector<std::string>& tokens)
    {
        int local_index;
        try { local_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid local index [0, 255]", tokens[2], LineID);
        }

        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index [0, 255]", tokens[2], LineID);
            return;
        }
        switch (local_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_word_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_word_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_word_2);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_word_3);
            break;
        default:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_word);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        }
    }
    void PopDWord(std::vector<std::string>& tokens)
    {
        int local_index;
        try { local_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid local index [0, 254]", tokens[2], LineID);
        }
        if(local_index > 254 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index [0, 254]", tokens[2], LineID);
            return;
        }
        switch (local_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_dword_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_dword_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_dword_2);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_dword_3);
            break;
        default:
            FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_dword);
            FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
            break;
        }
    }
    void PopWords(std::vector<std::string>& tokens)
    {
        int local_index;
        int count;
        try { local_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid local index [0, 255 - count]", tokens[2], LineID);
        }
        try { count = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid pop words count [0, 255]", tokens[3], LineID);
        }

        if(count < 0 || count > 255)
        {
            Errors.emplace_back("Invalid pop words count [0, 255]", tokens[3], LineID);
            return;
        }
        if(local_index + count > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index [0, 255 - count]", tokens[2], LineID);
            return;
        }
        FunctionsData[FunctionNames.back()].Opcodes.push_back(OpCodes::pop_words);
        FunctionsData[FunctionNames.back()].Opcodes.push_back(local_index);
        FunctionsData[FunctionNames.back()].Opcodes.push_back(count);
    }
    
    void Pop(std::vector<std::string>& tokens)
    {
        if(PopFunctions.contains(tokens[1]))
            PopFunctions.at(tokens[1])(tokens);
        else
            Errors.emplace_back("Invalid pop type", tokens[1], LineID);
    }
    
} // namespace BCC::Compiler
