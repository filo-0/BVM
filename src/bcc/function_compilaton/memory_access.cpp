#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    void Load(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens[1] == "byte")
        {
            int index;
            try { index = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                PushError("Invalid <b> parameter [0, 3]", tokens[2]);
            }
            switch (index)
            {
            case 0:
                opcodes.push_back(OpCodes::load_byte_0);
                break;
            case 1:
                opcodes.push_back(OpCodes::load_byte_1);
                break;
            case 2:
                opcodes.push_back(OpCodes::load_byte_2);
                break;
            case 3:
                opcodes.push_back(OpCodes::load_byte_3);
                break;
            default:
                PushError("Invalid <b> parameter [0, 3]", tokens[1]);
                return;
            }
        }
        else if(tokens[1] == "hword")
        {
            int index;
            try { index = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                PushError("Invalid <h> parameter {0, 2}", tokens[2]);
            }
            switch (index)
            {
            case 0:
                opcodes.push_back(OpCodes::load_hword_0);
                break;
            case 2:
                opcodes.push_back(OpCodes::load_hword_2);
                break;
            default:
                PushError("Invalid <h> parameter {0, 2}", tokens[1]);
                return;
            }
        }
        else if(tokens[1] == "word")
            opcodes.push_back(OpCodes::load_word);
        else if(tokens[1] == "dword")
            opcodes.push_back(OpCodes::load_dword);
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword}", tokens[1]);
    }
    void Store(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens[1] == "byte")
        {
            int index;
            try { index = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                PushError("Invalid <b> parameter [0, 3]", tokens[2]);
            }
            switch (index)
            {
            case 0:
                opcodes.push_back(OpCodes::store_byte_0);
                break;
            case 1:
                opcodes.push_back(OpCodes::store_byte_1);
                break;
            case 2:
                opcodes.push_back(OpCodes::store_byte_2);
                break;
            case 3:
                opcodes.push_back(OpCodes::store_byte_3);
                break;
            default:
                PushError("Invalid <b> parameter", tokens[1]);
                return;
            }
        }
        else if(tokens[1] == "hword")
        {
            int index;
            try { index = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                PushError("Invalid <h> parameter {0, 2}", tokens[2]);
            }
            switch (index)
            {
            case 0:
                opcodes.push_back(OpCodes::store_hword_0);
                break;
            case 2:
                opcodes.push_back(OpCodes::store_hword_2);
                break;
            default:
                PushError("Invalid <h> parameter {0, 2}", tokens[1]);
                return;
            }
        }
        else if(tokens[1] == "word")
            opcodes.push_back(OpCodes::store_word);
        else if(tokens[1] == "dword")
            opcodes.push_back(OpCodes::store_dword);
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword}", tokens[1]);
    }
} // namespace BCC::Compiler
