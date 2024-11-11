#include "bcc/functions.hpp"
#include "bcc/compiler.hpp"

namespace BCC
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
        if(tokens.size() != 4)
        {
            PushError("Invalid number of parameters {3}", tokens[0]);
            return;
        }
        int byte_index;
        int local_index;

        try { byte_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <b> parameter [0, 3]", tokens[2]);
        }
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
        switch (byte_index)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_byte_0);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;    
        case 1:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_byte_1);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_byte_2);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        case 3:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_byte_3);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        default:
            PushError("Invalid <b> parameter [0, 3]", tokens[2]);
            return;
        }
    }
    void PopHWord(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 4)
        {
            PushError("Invalid number of parameters {3}", tokens[0]);
            return;
        }
        int hword_index;
        int local_index;
        try { hword_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <h> parameter {0, 2}", tokens[2]);
        }
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
        switch (hword_index)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_hword_0);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_hword_2);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        default:
            PushError("Invalid <h> parameter {0, 2}", tokens[2]);
            return;
        }
    }
    void PopWord(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 3)
        {
            PushError("Invalid number of parameters {2}", tokens[0]);
            return;
        }
        int local_index;
        try { local_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[2]);
        }

        if(local_index > 255 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[2]);
            return;
        }
        switch (local_index)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_word_0);
            break;
        case 1:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_word_1);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_word_2);
            break;
        case 3:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_word_3);
            break;
        default:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_word);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        }
    }
    void PopDWord(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 3)
        {
            PushError("Invalid number of parameters {2}", tokens[0]);
            return;
        }
        int local_index;
        try { local_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <l> parameter [0, 254]", tokens[2]);
        }
        if(local_index > 254 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 254]", tokens[2]);
            return;
        }
        switch (local_index)
        {
        case 0:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_dword_0);
            break;
        case 1:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_dword_1);
            break;
        case 2:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_dword_2);
            break;
        case 3:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_dword_3);
            break;
        default:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_dword);
            GetCurrentFunctionOpcodesList().push_back(local_index);
            break;
        }
    }
    void PopWords(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 4)
        {
            PushError("Invalid number of parameters {3}", tokens[0]);
            return;
        }
        int local_index;
        int count;
        try { local_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <l> parameter [0, 255 - n]", tokens[2]);
        }
        try { count = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <n> parameter [0, 255]", tokens[3]);
        }

        if(count < 0 || count > 255)
            PushError("Invalid <n> parameter [0, 255] ", tokens[3]);

        if(local_index + count > 255 || local_index < 0)
            PushError("Invalid <l> parameter [0, 255 - n]", tokens[2]);

        GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_words);
        GetCurrentFunctionOpcodesList().push_back(local_index);
        GetCurrentFunctionOpcodesList().push_back(count);
    }
    
    void Pop(std::vector<std::string>& tokens)
    {
        if(PopFunctions.contains(tokens[1]))
            PopFunctions.at(tokens[1])(tokens);
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword}", tokens[1]);
    }
    
} // namespace BCC::Compiler
