#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
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
    const std::unordered_map<std::string, opcode> StoreBufferCodes = {
        {"byte", OpCodes::store_buffer_byte},
        {"hword", OpCodes::store_buffer_hword},
        {"word", OpCodes::store_buffer_word},
        {"dword", OpCodes::store_buffer_dword},
        {"words", OpCodes::store_buffer_words}
    };

    void LoadData(std::vector<std::string>& tokens);
    void LoadOffset(std::vector<std::string>& tokens);
    void LoadBuffer(std::vector<std::string>& tokens);

    void LoadBufferRef(std::vector<std::string>& tokens)
    {
        if(tokens.size() < 4)
        {
            PushError("Invalid number of parameters {3, 4}", tokens[0]);
            return;
        }

        auto& bytecodes = GetCurrentFunctionOpcodesList();
        if(LoadBufferRefCodes.contains(tokens[3]))
        {
            bytecodes.push_back(LoadBufferRefCodes.at(tokens[3]));


            if(tokens[3] == "words")
            {            
                if(tokens.size() != 5)
                {
                    PushError("Invalid number of parameters {4}", tokens[0]);
                    return;
                }
                int count;
                try { count = std::stoi(tokens[4]); }
                catch(const std::exception& e)
                {
                    PushError("Invalid <n> parameter", tokens[4]);
                }
                bytecodes.push_back(count);
            }
        }
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword, words}", tokens[3]);
    }
    void LoadBufferVal(std::vector<std::string>& tokens)
    {
        if(tokens.size() < 4)
        {
            PushError("Invalid number of parameters {3, 4}", tokens[0]);
            return;
        }

        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(LoadBufferValCodes.contains(tokens[3]))
        {
            opcodes.push_back(LoadBufferValCodes.at(tokens[3]));

            if(tokens[3] == "words")
            {
                if(tokens.size() != 5)
                {
                    PushError("Invalid number of parameters {4}", tokens[0]);
                    return;
                }
                int count;
                try { count = std::stoi(tokens[4]); }
                catch(const std::exception& e)
                {
                    PushError("Invalid <n> parameter", tokens[4]);
                }
                opcodes.push_back(count);
            }
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
        int index;
        try { index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
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
        int offset;
        try { offset = std::stoi(tokens[4]); }
        catch(std::exception& e)
        {
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        opcodes.push_back(offset);
    }
    void LoadOffsetHWord(std::vector<std::string>& tokens)
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
        int offset;
        try { offset = std::stoi(tokens[4]); }
        catch(std::exception& e)
        {
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[4]);
        opcodes.push_back(offset);
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
        int offset;
        try { offset = std::stoi(tokens[3]); }
        catch(std::exception& e)
        {
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
        opcodes.push_back(offset);
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
        int offset;
        try { offset = std::stoi(tokens[3]); }
        catch(std::exception& e)
        {
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
        }
        if(offset < 0 || offset > 255)
            PushError("Invalid <o> parameter [0, 255]", tokens[3]);
        opcodes.push_back(offset);
    }
    void LoadOffsetWords(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
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
            return;
        }
        opcodes.push_back(OpCodes::load_offset_words);
        opcodes.push_back(count);

        if(tokens.size() == 4)
        {
            PushError("Parameter <o> not found", tokens[0]);
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
        int index;
        try { index = std::stoi(tokens[3]); }
        catch(const std::exception& e)
        {
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
    }
    void LoadDataHWord(std::vector<std::string>& tokens)
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
            opcodes.push_back(OpCodes::load_hword_0);
            break;
        case 2:
            opcodes.push_back(OpCodes::load_hword_2);
            break;
        default:
            PushError("Invalid <h> parameter {0, 2}", tokens[3]);
            return;
        }
    }
    void LoadDataWord(std::vector<std::string>& tokens)
    {
        (void)tokens;
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::load_word);
    }
    void LoadDataDWord(std::vector<std::string>& tokens)
    {
        (void)tokens;
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::load_dword);
    }
    void LoadDataWords(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
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
            return;
        }
        opcodes.push_back(OpCodes::load_words);
        opcodes.push_back(count);
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
                if(tokens.size() != 4)
                {
                    PushError("Invalid number of parameters {3}", tokens[0]);
                    return;
                }
                int count;
                try { count = std::stoi(tokens[3]); }
                catch(const std::exception& e)
                {
                    PushError("Invalid <n> parameter", tokens[3]);
                }
                bytecodes.push_back(count);
            }
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
    }
    void StoreDataWord(std::vector<std::string>& tokens)
    {
        (void) tokens;
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::store_word);
    }
    void StoreDataDWord(std::vector<std::string>& tokens)
    {
        (void) tokens;
        auto& opcodes = GetCurrentFunctionOpcodesList();
        opcodes.push_back(OpCodes::store_dword);
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
