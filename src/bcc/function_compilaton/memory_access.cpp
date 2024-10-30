#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    void Load(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].Opcodes;
        if(tokens[1] == "byte")
        {
            int index;
            try { index = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                Errors.emplace_back("Invalid load byte index [0, 3]", tokens[2], LineID);
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
                Errors.emplace_back("Invalid load byte index [0, 3]", tokens[1], LineID);
                return;
            }
        }
        else if(tokens[1] == "hword")
        {
            int index;
            try { index = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                Errors.emplace_back("Invalid load hword index {0, 2}", tokens[2], LineID);
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
                Errors.emplace_back("Invalid load byte index {0, 2}", tokens[1], LineID);
                return;
            }
        }
        else if(tokens[1] == "word")
            opcodes.push_back(OpCodes::load_word);
        else if(tokens[1] == "dword")
            opcodes.push_back(OpCodes::load_dword);
        else
            Errors.emplace_back("Invalid load argument [type]", tokens[1], LineID);
    }
    void Store(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].Opcodes;
        if(tokens[1] == "byte")
        {
            int index;
            try { index = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                Errors.emplace_back("Invalid load byte index [0, 3]", tokens[2], LineID);
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
                Errors.emplace_back("Invalid load byte index [0, 3]", tokens[1], LineID);
                return;
            }
        }
        else if(tokens[1] == "hword")
        {
            int index;
            try { index = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                Errors.emplace_back("Invalid load hword index {0, 2}", tokens[2], LineID);
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
                Errors.emplace_back("Invalid load byte index {0, 2}", tokens[1], LineID);
                return;
            }
        }
        else if(tokens[1] == "word")
            opcodes.push_back(OpCodes::store_word);
        else if(tokens[1] == "dword")
            opcodes.push_back(OpCodes::store_dword);
        else
            Errors.emplace_back("Invalid load argument [type]", tokens[1], LineID);
    }
} // namespace BCC::Compiler
