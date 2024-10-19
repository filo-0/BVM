#include "bcc/function_compilation.hpp"
#include "bcc/codes_tables.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    void PushConst(std::vector<std::string>& tokens)
    {
        if(tokens[2].compare("word") == 0)
        {
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_word_from_pool);
            FunctionsData[FunctionNames.back()].opcodes.push_back(WordConstantsData[tokens[3]].index);
        }
        else if (tokens[2].compare("dword") == 0)
        {
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_dword_from_pool);
            FunctionsData[FunctionNames.back()].opcodes.push_back(DWordConstantsData[tokens[3]].index);
        }
        else
        {
            Errors.emplace_back("Invalid push const specifier", tokens[2], LineID);
        }
    }

    void PushLocalByte(std::vector<std::string>& tokens)
    {
        int byte_index = std::stoi(tokens[3]);
        int local_index = std::stoi(tokens[4]);

        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index", tokens[4], LineID);
            return;
        }
        switch (byte_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_byte_0);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;    
        case 1:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_byte_1);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_byte_2);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_byte_3);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        default:
            Errors.emplace_back("Invalid byte index", tokens[3], LineID);
        }
    }
    void PushLocalHWord(std::vector<std::string>& tokens)
    {
        int hword_index = std::stoi(tokens[3]);
        int local_index = std::stoi(tokens[4]);

        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index", tokens[4], LineID);
            return;
        }
        switch (hword_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_hword_0);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_hword_2);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        default:
            Errors.emplace_back("Invalid hword index", tokens[3], LineID);
        }
    }
    void PushLocalWord(std::vector<std::string>& tokens)
    {
        int local_index = std::stoi(tokens[3]);

        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index", tokens[3], LineID);
            return;
        }
        switch (local_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_word_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_word_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_word_2);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_word_3);
            break;
        default:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_word);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        }
    }
    void PushLocalDword(std::vector<std::string>& tokens)
    {
        int local_index = std::stoi(tokens[3]);

        if(local_index > 254 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index", tokens[3], LineID);
            return;
        }
        switch (local_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_dword_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_dword_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_dword_2);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_dword_3);
            break;
        default:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_dword);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        }
    }
    void PushLocalWords(std::vector<std::string>& tokens)
    {
        int local_index = std::stoi(tokens[3]);
        int count = std::stoi(tokens[4]);

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
        FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_words);
        FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
        FunctionsData[FunctionNames.back()].opcodes.push_back(count);
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
        int value = std::stoi(tokens[3]);
        if(value > 255 || value < 0)
        {
            Errors.emplace_back("Invalid value [0, 255]", tokens[3], LineID);
            return;
        }
        switch (value)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_word_value_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_i32_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_i32_2);
            break;
        default:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_i8_as_i32);
            FunctionsData[FunctionNames.back()].opcodes.push_back(value);
            break;
        }      
    }
    void PushAsI64(std::vector<std::string>& tokens)
    {
        int value = std::stoi(tokens[3]);
        if(value > 255 || value < 0)
        {
            Errors.emplace_back("Invalid value [0, 255]", tokens[3], LineID);
            return;
        }
        switch (value)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_dword_value_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_i64_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_i64_2);
            break;
        default:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_i8_as_i64);
            FunctionsData[FunctionNames.back()].opcodes.push_back(value);
            break;
        }
    }
    void PushAsF32(std::vector<std::string>& tokens)
    {
        int value = std::stoi(tokens[3]);
        switch (value)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_word_value_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_f32_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_f32_2);
            break;
        default:
            Errors.emplace_back("Value out of range {0, 1, 2}", tokens[3], LineID);
            break;
        }
    }
    void PushAsF64(std::vector<std::string>& tokens)
    {
        int value = std::stoi(tokens[3]);
        switch (value)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_dword_value_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_f64_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::push_f64_2);
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

    void Push(std::vector<std::string>& tokens)
    {
        if(PushFunctions.contains(tokens[1]))
            PushFunctions.at(tokens[1])(tokens);
        else
            Errors.emplace_back("Invalid push specifier", tokens[1], LineID);
    }

    void PopByte(std::vector<std::string>& tokens)
    {
        int byte_index = std::stoi(tokens[2]);
        int local_index = std::stoi(tokens[3]);
        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index", tokens[3], LineID);
            return;
        }
        switch (byte_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_byte_0);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;    
        case 1:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_byte_1);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_byte_2);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_byte_3);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        default:
            Errors.emplace_back("Invalid byte index", tokens[2], LineID);
            return;
        }
    }
    void PopHWord(std::vector<std::string>& tokens)
    {
        int hword_index = std::stoi(tokens[2]);
        int local_index = std::stoi(tokens[3]);
        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index [0, 255]", tokens[3], LineID);
            return;
        }
        switch (hword_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_hword_0);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_hword_2);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        default:
            Errors.emplace_back("Invalid hword index [0, 255]", tokens[2], LineID);
            return;
        }
    }
    void PopWord(std::vector<std::string>& tokens)
    {
        int local_index = std::stoi(tokens[2]);
        if(local_index > 255 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index [0, 255]", tokens[2], LineID);
            return;
        }
        switch (local_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_word_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_word_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_word_2);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_word_3);
            break;
        default:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_word);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        }
    }
    void PopDWord(std::vector<std::string>& tokens)
    {
        int local_index = std::stoi(tokens[2]);
        if(local_index > 254 || local_index < 0)
        {
            Errors.emplace_back("Invalid local index [0, 254]", tokens[2], LineID);
            return;
        }
        switch (local_index)
        {
        case 0:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_dword_0);
            break;
        case 1:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_dword_1);
            break;
        case 2:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_dword_2);
            break;
        case 3:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_dword_3);
            break;
        default:
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_dword);
            FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
            break;
        }
    }
    void PopWords(std::vector<std::string>& tokens)
    {
        int local_index = std::stoi(tokens[2]);
        int count = std::stoi(tokens[3]);
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
        FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::pop_words);
        FunctionsData[FunctionNames.back()].opcodes.push_back(local_index);
        FunctionsData[FunctionNames.back()].opcodes.push_back(count);
    }
    void Pop(std::vector<std::string>& tokens)
    {
        if(PopFunctions.contains(tokens[1]))
            PopFunctions.at(tokens[1])(tokens);
        else
            Errors.emplace_back("Invalid pop type", tokens[1], LineID);
    }
    
    void Add(std::vector<std::string>& tokens)
    {
        if(AddCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(AddCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }
    void Sub(std::vector<std::string>& tokens)
    {
        if(SubCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(SubCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }
    void Mul(std::vector<std::string>& tokens)
    {
        if(MulCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(MulCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }
    void Div(std::vector<std::string>& tokens)
    {
        if(DivCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(DivCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }
    
    void And(std::vector<std::string>& tokens)
    {
        if(AndCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(AndCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }
    void Or(std::vector<std::string>& tokens)
    {
        if(OrCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(OrCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }
    void Xor(std::vector<std::string>& tokens)
    {
        if(XorCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(XorCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }
    void Not(std::vector<std::string>& tokens)
    {
        if(NotCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(NotCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }
    void Shl(std::vector<std::string>& tokens)
    {
        if(ShlCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(ShlCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }
    void Shr(std::vector<std::string>& tokens)
    {
        if(ShrCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(ShrCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }

    void Cast(std::vector<std::string>& tokens)
    {
        if(CastCodes.contains({ tokens[1], tokens[2] }))
            FunctionsData[FunctionNames.back()].opcodes.push_back(CastCodes.at({ tokens[1], tokens[2] }));
        else
            Errors.emplace_back("Invalid type cast", tokens[1] + std::string(" to ") + tokens[2], LineID);
    }
    void Syscall(std::vector<std::string>& tokens)
    {
        FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::syscall);
        if(SyscallsCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(SyscallsCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid syscall function", tokens[1], LineID);
    }
    void Return(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::return_void);
        else if(ReturnCodes.contains(tokens[1]))
            FunctionsData[FunctionNames.back()].opcodes.push_back(ReturnCodes.at(tokens[1]));
        else
            Errors.emplace_back("Invalid return type", tokens[1], LineID);
    }

    void Call(std::vector<std::string>& tokens)
    {
        if(FunctionsData.contains(tokens[1]))
        {
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::call);

            u16 idx = FunctionsData[tokens[1]].index;
            FunctionsData[FunctionNames.back()].opcodes.push_back(idx);
            FunctionsData[FunctionNames.back()].opcodes.push_back(idx >> 8);
        }
        else
            Errors.emplace_back("Function not found", tokens[1], LineID);
    }


    void Jump(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 2)
        {
            FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::jmp);
            int offset = std::stoi(tokens[1]);
            if(offset > 0x7fff || offset < -0x8000)
            {
                Errors.emplace_back("Invalid jump offset [-32768, 32767]", tokens[1], LineID);
                return;
            }
            FunctionsData[FunctionNames.back()].opcodes.push_back(offset);
            FunctionsData[FunctionNames.back()].opcodes.push_back(offset >> 8);
        }
        else if(tokens.size() == 4)
        {
            if(tokens[1] == "eq")
            {
                if(tokens[2] == "i32")
                {
                    FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::jmp_i32_eq);
                    int offset = std::stoi(tokens[3]);
                    if(offset > 0x7fff || offset < -0x8000)
                    {
                        Errors.emplace_back("Invalid jump offset [-32768, 32767]", tokens[3], LineID);
                        return;
                    }
                    FunctionsData[FunctionNames.back()].opcodes.push_back(offset);
                    FunctionsData[FunctionNames.back()].opcodes.push_back(offset >> 8);
                }           
            }
            if(tokens[1] == "gt")
            {
                if(tokens[2] == "i32")
                {
                    FunctionsData[FunctionNames.back()].opcodes.push_back(OpCodes::jmp_i32_gt);
                    int offset = std::stoi(tokens[3]);
                    if(offset > 0x7fff || offset < -0x8000)
                    {
                        Errors.emplace_back("Invalid jump offset [-32768, 32767]", tokens[3], LineID);
                        return;
                    }
                    FunctionsData[FunctionNames.back()].opcodes.push_back(offset);
                    FunctionsData[FunctionNames.back()].opcodes.push_back(offset >> 8);
                }           
            }
        }
        else
            Errors.emplace_back("Label not found", tokens[1], LineID);
    }
}