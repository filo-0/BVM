#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    const std::unordered_map<std::string, opcode> StoreBufferCodes = {
        {"byte", OpCodes::store_buffer_byte},
        {"hword", OpCodes::store_buffer_hword},
        {"word", OpCodes::store_buffer_word},
        {"dword", OpCodes::store_buffer_dword},
        {"words", OpCodes::store_buffer_words}
    };

    void StoreBuffer(std::vector<std::string>& tokens)
    {
        auto& bytecodes = GetCurrentFunctionOpcodesList();

        if(tokens.size() < 3)
        {
            PushError("Invalid number of parameters {2, 3}", tokens[0]);
            return;
        }

        if(StoreBufferCodes.contains(tokens[2]))
        {
            bytecodes.push_back(StoreBufferCodes.at(tokens[2]));

            if(tokens[2] == "words")
            {
                if(tokens.size() == 3)
                {
                    PushError("No parameter <n> found", tokens[0]);
                    return;
                }
                int count;
                try { count = std::stoi(tokens[3]); }
                catch(const std::exception& e)
                {
                    PushError("Invalid <n> parameter", tokens[3]);
                }
                if(count < 0 || count > 255)
                    PushError("Invalid <n> parameter [0, 255]", tokens[3]);
                bytecodes.push_back(count);

                if(tokens.size() > 4)
                    PushError("Too many parameters found", tokens[0]);
            }
            else if(tokens.size() > 3)
                PushError("Too many parameters found", tokens[0]);
        }
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword, words}", tokens[2]);
    }

    void StoreDataByte(std::vector<std::string>& tokens);
    void StoreDataHWord(std::vector<std::string>& tokens);
    void StoreDataWord(std::vector<std::string>& tokens);
    void StoreDataDWord(std::vector<std::string>& tokens);
    void StoreDataWords(std::vector<std::string>& tokens);

    const std::unordered_map<std::string, CompileFlowFuntion> StoreDataFuncs
    {
        {"byte", StoreDataByte},
        {"hword", StoreDataHWord},
        {"word", StoreDataWord},
        {"dword", StoreDataDWord},
        {"words", StoreDataWords}
    };

    void StoreDataByte(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No parameter <b> found [0, 3]", tokens[0]);
            return;
        }

        int index;
        try { index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <b> parameter [0, 3]", tokens[3]);
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
            PushError("Invalid <b> parameter", tokens[3]);
            return;
        }
        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    void StoreDataHWord(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No parameter <b> found {0, 2}", tokens[0]);
            return;
        }
        int index;
        try { index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <b> parameter {0, 2}", tokens[3]);
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
            PushError("Invalid <b> parameter {0, 2}", tokens[3]);
            return;
        }
        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    void StoreDataWord(std::vector<std::string>& tokens)
    {
        (void) tokens;
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::store_word);
        
        if(tokens.size() > 3)
            PushError("Too many parameters found", tokens[0]);
    }
    void StoreDataDWord(std::vector<std::string>& tokens)
    {
        (void) tokens;
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::store_dword);

        if(tokens.size() > 3)
            PushError("Too many parameters found", tokens[0]);
    }
    void StoreDataWords(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No parameter <n> found [0, 255]", tokens[0]);
            return;
        }
        int count;
        try { count = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <n> parameter", tokens[3]);
            return;
        }
        opcodes.push_back(OpCodes::store_words);
        opcodes.push_back(count);

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }

    void StoreData(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 2)
        {
            PushError("No parameter <t> found {byte, hword, word, dword, words}", tokens[0]);
            return;
        }

        if(StoreDataFuncs.contains(tokens[2]))
        {
            CompileFlowFuntion f = StoreDataFuncs.at(tokens[2]);
            f(tokens);
        }
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword}", tokens[2]);
    }

    void StoreOffsetByte(std::vector<std::string>& tokens);
    void StoreOffsetHWord(std::vector<std::string>& tokens);
    void StoreOffsetWord(std::vector<std::string>& tokens);
    void StoreOffsetDWord(std::vector<std::string>& tokens);
    void StoreOffsetWords(std::vector<std::string>& tokens);

    const std::unordered_map<std::string, CompileFlowFuntion> StoreOffsetFuncs = 
    {
        { "byte", StoreOffsetByte },
        { "hword", StoreOffsetHWord },
        { "word", StoreOffsetWord },
        { "dword", StoreOffsetDWord },
        { "words", StoreOffsetWords },
    };

    void StoreOffsetByte(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No parameter <b> found [0, 3]", tokens[0]);
            return;
        }

        int index;
        try { index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <b> parameter [0, 3]", tokens[3]);
        }
        switch (index)
        {
        case 0:
            opcodes.push_back(OpCodes::store_offset_byte_0);
            break;
        case 1:
            opcodes.push_back(OpCodes::store_offset_byte_1);
            break;
        case 2:
            opcodes.push_back(OpCodes::store_offset_byte_2);
            break;
        case 3:
            opcodes.push_back(OpCodes::store_offset_byte_3);
            break;
        default:
            PushError("Invalid <b> parameter", tokens[3]);
            return;
        }

        if(tokens.size() == 4)
        {
            PushError("No parameter <o> found [0, 255]", tokens[4]);
            return;
        }

        int offset;
        try { offset = std::stoi(tokens[4]); }
        catch(std::exception& e)
        {
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        opcodes.push_back(offset);

        if(tokens.size() > 5)
            PushError("Too many parameters found", tokens[0]);
    }
    void StoreOffsetHWord(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No parameter <b> found {0, 2}", tokens[0]);
            return;
        }
        int index;
        try { index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <b> parameter {0, 2}", tokens[3]);
        }
        switch (index)
        {
        case 0:
            opcodes.push_back(OpCodes::store_offset_hword_0);
            break;
        case 2:
            opcodes.push_back(OpCodes::store_offset_hword_2);
            break;
        default:
            PushError("Invalid <b> parameter {0, 2}", tokens[3]);
            return;
        }

        if(tokens.size() == 4)
        {
            PushError("No parameter <o> found [0, 255]", tokens[0]);
            return;
        }

        int offset;
        try { offset = std::stoi(tokens[4]); }
        catch(std::exception& e)
        {
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);

        opcodes.push_back(offset);

        if(tokens.size() > 5)
            PushError("Too many parameters found", tokens[0]);
    }
    void StoreOffsetWord(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::store_offset_word);

        if(tokens.size() == 3)
        {
            PushError("No parameter <o> found [0, 255]", tokens[0]);
            return;
        }
        int offset;
        try { offset = std::stoi(tokens[3]); }
        catch(std::exception& e)
        {
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);

        opcodes.push_back(offset);

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    void StoreOffsetDWord(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::store_offset_dword);

        if(tokens.size() == 3)
        {
            PushError("No parameter <o> found [0, 255]", tokens[0]);
            return;
        }
        int offset;
        try { offset = std::stoi(tokens[3]); }
        catch(std::exception& e)
        {
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);

        opcodes.push_back(offset);

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    void StoreOffsetWords(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No parameter <o> found [0, 255]", tokens[0]);
            return;
        }

        int offset;
        try { offset = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
            return;
        }
        opcodes.push_back(OpCodes::store_offset_words);
        opcodes.push_back(offset);

        if(tokens.size() == 4)
        {
            PushError("No parameter <n> found [0, 255]", tokens[0]);
            return;
        }
        int count;
        try { count = std::stoi(tokens[4]); }
        catch(std::exception& e)
        {
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        }
        if(count < 0 || count > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);

        opcodes.push_back(count);

        if(tokens.size() > 5)
            PushError("Too many parameters found", tokens[0]);
    }

    void StoreOffset(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 2)
        {
            PushError("No parameter <t> found {byte, hword, word, dword, words}", tokens[0]);
            return;
        }
        if(StoreOffsetFuncs.contains(tokens[2]))
        {
            CompileFlowFuntion f = StoreOffsetFuncs.at(tokens[2]);
            f(tokens);
        }
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword, words}", tokens[2]);
    }

    void Store(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No store specifier found", tokens[0]);
            return;
        }
        if(tokens[1] == "buffer")
            StoreBuffer(tokens);
        else if(tokens[1] == "data")
            StoreData(tokens);
        else if(tokens[1] == "offset")
            StoreOffset(tokens);
        else
            PushError("Invalid load specifier {buffer, data, offset}", tokens[1]);
    }
} // namespace BCC::Compiler
