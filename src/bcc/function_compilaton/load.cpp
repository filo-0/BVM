#include "bcc/functions.hpp"
#include "bcc/compiler.hpp"

namespace BCC
{
    const std::unordered_map<std::string, opcode> LoadBufferRefCodes = {
        {"byte", OpCodes::load_buffer_byte_ref},
        {"hword", OpCodes::load_buffer_hword_ref},
        {"word", OpCodes::load_buffer_word_ref},
        {"dword", OpCodes::load_buffer_dword_ref},
        {"words", OpCodes::load_buffer_words_ref}
    };
    const std::unordered_map<std::string, opcode> LoadBufferValCodes = {
        {"byte", OpCodes::load_buffer_byte_val},
        {"hword", OpCodes::load_buffer_hword_val},
        {"word", OpCodes::load_buffer_word_val},
        {"dword", OpCodes::load_buffer_dword_val},
        {"words", OpCodes::load_buffer_words_val}
    };

    void LoadData(std::vector<std::string>& tokens);
    void LoadOffset(std::vector<std::string>& tokens);
    void LoadBuffer(std::vector<std::string>& tokens);

    void LoadBufferRef(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 3)
        {
            PushError("No parameter <t> found {byte, hword, word, dword, words}", tokens[0]);
            return;
        }

        auto& bytecodes = GetCurrentFunctionOpcodesList();
        if(LoadBufferRefCodes.contains(tokens[3]))
        {
            bytecodes.push_back(LoadBufferRefCodes.at(tokens[3]));

            if(tokens[3] == "words")
            {            
                if(tokens.size() == 4)
                {
                    PushError("No parameter <n> found", tokens[0]);
                    return;
                }
                int count = 0;
                try { count = std::stoi(tokens[4]); }
                catch(const std::exception& e)
                {
					(void)e;
                    PushError("Invalid <n> parameter", tokens[4]);
                }
                if(count < 0 || count > 255)
                    PushError("Invalid <n> parameter [0, 255]", tokens[4]);
                bytecodes.push_back((opcode)count);

                if(tokens.size() > 5)
                    PushError("Too many parameters found", tokens[0]);
            }
            else if(tokens.size() > 4)
                PushError("Too many parameters found", tokens[0]);
        }
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword, words}", tokens[3]);
    }
    void LoadBufferVal(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 3)
        {
            PushError("No parameter <t> found {byte, hword, word, dword, words}", tokens[0]);
            return;
        }

        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(LoadBufferValCodes.contains(tokens[3]))
        {
            opcodes.push_back(LoadBufferValCodes.at(tokens[3]));

            if(tokens[3] == "words")
            {
                if(tokens.size() == 4)
                {
                    PushError("No parameter <n> found", tokens[0]);
                    return;
                }

                int count = 0;
                try { count = std::stoi(tokens[4]); }
                catch(const std::exception& e)
                {
                    (void)e;
                    PushError("Invalid <n> parameter", tokens[4]);
                }
                if(count < 0 || count > 255)
                    PushError("Invalid <n> parameter [0, 255]", tokens[4]);
                opcodes.push_back((opcode)count);

                if(tokens.size() > 5)
                    PushError("Too many parameters found", tokens[0]);
            }
            else if(tokens.size() > 4)
                PushError("Too many parameters found", tokens[0]);
        }
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword, words}", tokens[3]);
    }
    
    void LoadBuffer(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 2)
        {
            PushError("No parameter <v> found {ref, val}", tokens[0]);
            return;
        }
        if(tokens[2] == "ref")
            LoadBufferRef(tokens);
        else if(tokens[2] == "val")
            LoadBufferVal(tokens);
        else
            PushError("Invalid <v> parameter {ref, val}", tokens[2]);
    }

    void LoadOffsetByte(std::vector<std::string>& tokens);
    void LoadOffsetHWord(std::vector<std::string>& tokens);
    void LoadOffsetWord(std::vector<std::string>& tokens);
    void LoadOffsetDWord(std::vector<std::string>& tokens);
    void LoadOffsetWords(std::vector<std::string>& tokens);

    const std::unordered_map<std::string, CompileFlowFuntion> LoadOffsetFuncs
    {
        {"byte", LoadOffsetByte},
        {"hword", LoadOffsetHWord},
        {"word", LoadOffsetWord},
        {"dword", LoadOffsetDWord},
        {"words", LoadOffsetWords}
    };

    void LoadOffsetByte(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No <b> parameter found [0, 3]", tokens[0]);
            return;
        }
        int index = 0;
        try { index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <b> parameter [0, 3]", tokens[3]);
        }
        switch (index)
        {
        case 0:
            opcodes.push_back(OpCodes::load_offset_byte_0);
            break;
        case 1:
            opcodes.push_back(OpCodes::load_offset_byte_1);
            break;
        case 2:
            opcodes.push_back(OpCodes::load_offset_byte_2);
            break;
        case 3:
            opcodes.push_back(OpCodes::load_offset_byte_3);
            break;
        default:
            PushError("Invalid <b> parameter [0, 3]", tokens[3]);
            break;
        }

        if(tokens.size() == 4)
        {
            PushError("Parameter <o> not found", tokens[0]);
            return;
        }
        int offset = 0;
        try { offset = std::stoi(tokens[4]); }
        catch(std::exception& e)
        {
            (void)e;
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        opcodes.push_back((opcode)offset);

        if(tokens.size() > 5)
            PushError("Too many parameters found", tokens[0]);
    }
    void LoadOffsetHWord(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No parameter <b> found {0, 2}", tokens[0]);
            return;
        }
        int index = 0;
        try { index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <b> parameter {0, 2}", tokens[3]);
        }
        switch (index)
        {
        case 0:
            opcodes.push_back(OpCodes::load_offset_hword_0);
            break;
        case 2:
            opcodes.push_back(OpCodes::load_offset_hword_2);
            break;
        default:
            PushError("Invalid <h> parameter {0, 2}", tokens[3]);
            return;
        }

        if(tokens.size() == 4)
        {
            PushError("Parameter <o> not found", tokens[0]);
            return;
        }
        int offset = 0;
        try { offset = std::stoi(tokens[4]); }
        catch(std::exception& e)
        {
            (void)e;
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        opcodes.push_back((opcode)offset);

        if(tokens.size() > 5)
            PushError("Too many parameters found", tokens[0]);
    }
    void LoadOffsetWord(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::load_offset_word);

        if(tokens.size() == 3)
        {
            PushError("Parameter <o> not found", tokens[0]);
            return;
        }
        int offset = 0;
        try { offset = std::stoi(tokens[3]); }
        catch(std::exception& e)
        {
            (void)e;
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
        opcodes.push_back((opcode)offset);

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    void LoadOffsetDWord(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::load_offset_dword);

        if(tokens.size() == 3)
        {
            PushError("Parameter <o> not found", tokens[0]);
            return;
        }
        int offset = 0;
        try { offset = std::stoi(tokens[3]); }
        catch(std::exception& e)
        {
            (void)e;
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
        opcodes.push_back((opcode)offset);

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    void LoadOffsetWords(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No parameter <n> found", tokens[0]);
            return;
        }

        int count = 0;
        try { count = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <n> parameter", tokens[3]);
            return;
        }
        opcodes.push_back(OpCodes::load_offset_words);
        opcodes.push_back((opcode)count);

        if(tokens.size() == 4)
        {
            PushError("Parameter <o> not found", tokens[0]);
            return;
        }
        int offset = 0;
        try { offset = std::stoi(tokens[4]); }
        catch(std::exception& e)
        {
            (void)e;
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        opcodes.push_back((opcode)offset);

        if(tokens.size() > 5)
            PushError("Too many parameters found", tokens[0]);
    }

    void LoadOffset(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 2)
        {
            PushError("No parameter <t> found {byte, hword, word, dword, words}", tokens[0]);
            return;
        }

        if(LoadOffsetFuncs.contains(tokens[2]))
        {
            CompileFlowFuntion f = LoadOffsetFuncs.at(tokens[2]);
            f(tokens);
        }
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword, words}", tokens[2]);
    }

    void LoadDataByte(std::vector<std::string>& tokens);
    void LoadDataHWord(std::vector<std::string>& tokens);
    void LoadDataWord(std::vector<std::string>& tokens);
    void LoadDataDWord(std::vector<std::string>& tokens);
    void LoadDataWords(std::vector<std::string>& tokens);

    const std::unordered_map<std::string, CompileFlowFuntion> LoadDataFuncs
    {
        {"byte", LoadDataByte},
        {"hword", LoadDataHWord},
        {"word", LoadDataWord},
        {"dword", LoadDataDWord},
        {"words", LoadDataWords}
    };

    void LoadDataByte(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No <b> parameter found [0, 3]", tokens[0]);
            return;
        }
        int index = 0;
        try { index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
			(void)e;
            PushError("Invalid <b> parameter [0, 3]", tokens[3]);
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
            PushError("Invalid <b> parameter [0, 3]", tokens[3]);
            return;
        }

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    void LoadDataHWord(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No parameter <b> found {0, 2}", tokens[0]);
            return;
        }
        int index = 0;
        try { index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
			(void)e;
            PushError("Invalid <b> parameter {0, 2}", tokens[3]);
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
            PushError("Invalid <h> parameter {0, 2}", tokens[3]);
            return;
        }

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    void LoadDataWord(std::vector<std::string>& tokens)
    {
        (void)tokens;
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::load_word);

        if(tokens.size() > 3)
            PushError("Too many parameters found", tokens[0]);
    }
    void LoadDataDWord(std::vector<std::string>& tokens)
    {
        (void)tokens;
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::load_dword);

        if(tokens.size() > 3)
            PushError("Too many parameters found", tokens[0]);
    }
    void LoadDataWords(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 3)
        {
            PushError("No parameter <n> found", tokens[0]);
            return;
        }

        int count = 0;
        try { count = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
            (void)e;
            PushError("Invalid <n> parameter", tokens[3]);
            return;
        }
        if(count < 0 || count > 255)
            PushError("Invalid <n> parameter [0, 255]", tokens[3]);

        opcodes.push_back(OpCodes::load_words);
        opcodes.push_back((opcode)count);

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
    
    void LoadData(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 2)
        {
            PushError("No parameter <t> found {byte, hword, word, dword, words}", tokens[0]);
            return;
        }

        if(LoadDataFuncs.contains(tokens[2]))
        {
            CompileFlowFuntion f = LoadDataFuncs.at(tokens[2]);
            f(tokens);
        }
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword, words}", tokens[2]);
    }
    
    void Load(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No load specifier found", tokens[0]);
            return;
        }

        if(tokens[1] == "buffer")
        {
            LoadBuffer(tokens);
        }
        else if(tokens[1] == "offset")
        {
            LoadOffset(tokens);
        }
        else if(tokens[1] == "data")
        {
            LoadData(tokens);
        }
        else
            PushError("Invalid load variant {buffer, offset, data}", tokens[1]);
    }
} // namespace BCC::Compiler
