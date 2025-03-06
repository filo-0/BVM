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
        if(tokens.size() == 2)
        {
            PushError("No parameter <b> found", tokens[0]);
            return;
        }
        int byte_index = 0;
        try { byte_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <b> parameter [0, 3]", tokens[2]);
        }
        if(byte_index > 3 || byte_index < 0)
        {
            PushError("Invalid <b> parameter [0, 3]", tokens[2]);
            return;
        }

        if(tokens.size() == 3)
        {
            PushError("No parameter <l> found [0, 255]", tokens[0]);
            return;
        }
        int local_index = 0;
        try { local_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <l> parameter [0, 255]", tokens[3]);
        }
        if(local_index > 255 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[3]);
            return;
        }


        auto& opcodes = GetCurrentFunctionOpcodesList();
        switch (byte_index)
        {
        case 0:
            opcodes.push_back(OpCodes::pop_byte_0);
            break;
        case 1:
            opcodes.push_back(OpCodes::pop_byte_1);
            break;
        case 2:
            opcodes.push_back(OpCodes::pop_byte_2);
            break;
        case 3:
            opcodes.push_back(OpCodes::pop_byte_3);
            break;
        default:
            std::cerr << "Invalid byte index" << std::endl;
            break;
        }
        opcodes.push_back((opcode)local_index);

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    void PopHWord(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 2)
        {
            PushError("No parameter <b> found", tokens[0]);
            return;
        }
        int hword_index = 0;
        try { hword_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <b> parameter {0, 2}", tokens[2]);
        }
        if(hword_index != 2 && hword_index != 0)
        {
            PushError("Invalid <b> parameter {0, 2}", tokens[2]);
            return;
        }

        if(tokens.size() == 3)
        {
            PushError("No parameter <l> found [0, 255]", tokens[0]);
            return;
        }
        int local_index = 0;
        try { local_index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <l> parameter [0, 255]", tokens[3]);
        }
        if(local_index > 255 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[3]);
            return;
        }


        auto& opcodes = GetCurrentFunctionOpcodesList();
        switch (hword_index)
        {
        case 0:
            opcodes.push_back(OpCodes::pop_hword_0);
            break;
        case 2:
            opcodes.push_back(OpCodes::pop_hword_2);
            break;
        default:
            std::cerr << "Invalid hword index" << std::endl;
            break;
        }
        opcodes.push_back((opcode)local_index);

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    void PopWord(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 3)
        {
            PushError("Invalid number of parameters {2}", tokens[0]);
            return;
        }
        int local_index = 0;
        try { local_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <l> parameter [0, 255]", tokens[2]);
        }

        if(local_index > 255 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 255]", tokens[2]);
            return;
        }

        auto& opcodes = GetCurrentFunctionOpcodesList();
        switch (local_index)
        {
        case 0:
            opcodes.push_back(OpCodes::pop_word_0);
            break;
        case 1:
            opcodes.push_back(OpCodes::pop_word_1);
            break;
        case 2:
            opcodes.push_back(OpCodes::pop_word_2);
            break;
        case 3:
            opcodes.push_back(OpCodes::pop_word_3);
            break;
        default:
            GetCurrentFunctionOpcodesList().push_back(OpCodes::pop_word);
            GetCurrentFunctionOpcodesList().push_back((opcode)local_index);
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
        int local_index = 0;
        try { local_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <l> parameter [0, 254]", tokens[2]);
        }
        if(local_index > 254 || local_index < 0)
        {
            PushError("Invalid <l> parameter [0, 254]", tokens[2]);
            return;
        }
        auto& opcodes = GetCurrentFunctionOpcodesList();
        switch (local_index)
        {
        case 0:
            opcodes.push_back(OpCodes::pop_dword_0);
            break;
        case 1:
            opcodes.push_back(OpCodes::pop_dword_1);
            break;
        case 2:
            opcodes.push_back(OpCodes::pop_dword_2);
            break;
        case 3:
            opcodes.push_back(OpCodes::pop_dword_3);
            break;
        default:
            opcodes.push_back(OpCodes::pop_dword);
            opcodes.push_back((opcode)local_index);
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
        int local_index = 0;
        int count       = 0;
        try { local_index = std::stoi(tokens[2]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <l> parameter [0, 255 - n]", tokens[2]);
        }
        try { count = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <n> parameter [0, 255]", tokens[3]);
        }

        if(count < 0 || count > 255)
            PushError("Invalid <n> parameter [0, 255] ", tokens[3]);

        if(local_index + count > 255 || local_index < 0)
            PushError("Invalid <l> parameter [0, 255 - n]", tokens[2]);

        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::pop_words);
        opcodes.push_back((opcode)local_index);
        opcodes.push_back((opcode)count);
    }
    
    void Pop(std::vector<std::string>& tokens)
    {
        if(PopFunctions.contains(tokens[1]))
            PopFunctions.at(tokens[1])(tokens);
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword}", tokens[1]);
    }
    
} // namespace BCC::Compiler
