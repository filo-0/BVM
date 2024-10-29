#include <stdexcept>

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
        int value;
        try { value = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid value", tokens[3], LineID);
        }

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
        int value;
        try { value = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            Errors.emplace_back("Invalid value", tokens[3], LineID);
        }
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
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].opcodes;
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
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].opcodes;
        if(CastCodes.contains(tokens[1]))
        {
            auto& table = CastCodes.at(tokens[1]);
            if(table.contains(tokens[2]))
            {
                opcode op = table.at(tokens[2]);
                opcodes.push_back(op);
            }
            else
                Errors.emplace_back("Invalid cast param [to]", tokens[2], LineID);
        }
        else
            Errors.emplace_back("Invalid cast param [from]", tokens[1], LineID);
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
            std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].opcodes;
            opcodes.push_back(OpCodes::call);

            u16 idx = FunctionsData[tokens[1]].index;
            opcodes.push_back(idx);
            opcodes.push_back(idx >> 8);
        }
        else
            Errors.emplace_back("Function not found", tokens[1], LineID);
    }

    void Dup(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].opcodes;
        if(tokens.size() == 2)
        {
            auto& table = DupCodes.at("x0");
            if(table.contains(tokens[1]))
            {
                opcode op = table.at(tokens[1]);
                opcodes.push_back(op);
            }
            else
                Errors.emplace_back("Invalid dup parameter [value_type]", tokens[1], LineID);
        }
        else if(tokens.size() == 3)
        {
            if(DupCodes.contains(tokens[1]))
            {
                auto& table = DupCodes.at(tokens[1]);
                if (table.contains(tokens[2]))
                {
                    opcode op = table.at(tokens[2]);
                    opcodes.push_back(op);
                }
                else
                    Errors.emplace_back("Invalid dup " + tokens[1] + " parameter [value_type]", tokens[2], LineID);
            }
            else
                Errors.emplace_back("Invalid dup parameter [dup_type]", tokens[1], LineID);
        }
        else
            Errors.emplace_back("Invalid dup args count", "None", LineID);
    }
    void Swap(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].opcodes;
        if(tokens[1] == "word")
            opcodes.push_back(OpCodes::swap_word);
        else if(tokens[1] == "dword")
            opcodes.push_back(OpCodes::swap_dword);
        else    
            Errors.emplace_back("Invalid swap type", tokens[1], LineID);
    }

    void Label(std::vector<std::string>& tokens)
    {
        LabelPointers[tokens[1]] = FunctionsData[FunctionNames.back()].opcodes.size();
    }
    void Jump(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].opcodes;
        if(tokens.size() == 2)
        {
            opcodes.push_back(OpCodes::jmp);
            opcodes.push_back(0);
            opcodes.push_back(0);
            Jumps.emplace_back(tokens[1], opcodes.size());
        }
        else if(tokens.size() == 4)
        {
            if(JumpCodes.contains(tokens[1]))
            {
                auto& table = JumpCodes.at(tokens[1]);
                if(table.contains(tokens[2]))
                {
                    opcode op = table.at(tokens[2]);
                    opcodes.push_back(op);  
                }
                else
                    Errors.emplace_back("Invalid jump " + tokens[1] + " type", tokens[2], LineID);                             
            }
            else
                Errors.emplace_back("Invalid jump coondition", tokens[1], LineID);
            
            opcodes.push_back(0);
            opcodes.push_back(0);
            Jumps.emplace_back(tokens[3], opcodes.size());
        }
        else
            Errors.emplace_back("Label not found", tokens[1], LineID);
    }

    void Inc(std::vector<std::string>& tokens)
    {
        if(IncCodes.contains(tokens[1]))
        {
            std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].opcodes;
            opcodes.push_back(IncCodes.at(tokens[1]));
            int local;
            try { local = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                Errors.emplace_back("Invalid local index [0, 255]", tokens[2], LineID);
            }
            if(local > 255 || local < 0)
                Errors.emplace_back("Invalid local index [0, 255]", tokens[2], LineID);
            opcodes.push_back(local);
        }
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }
    void Dec(std::vector<std::string>& tokens)
    {
        if(DecCodes.contains(tokens[1]))
        {
            if(!DecCodes.contains(tokens[1]))
                Errors.emplace_back("Invalid dec type", tokens[1], LineID);
            
            std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].opcodes;
            opcodes.push_back(DecCodes.at(tokens[1]));
            int local;
            try { local = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                Errors.emplace_back("Invalid local index [0, 255]", tokens[2], LineID);
            }
            if(local > 255 || local < 0)
                Errors.emplace_back("Invalid local index [0, 255]", tokens[2], LineID);
            opcodes.push_back(local);
        }
        else
            Errors.emplace_back("Invalid type", tokens[1], LineID);
    }

    void Load(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].opcodes;
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
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].opcodes;
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
}