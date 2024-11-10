# Syntax
During the documentation it's used the following syntax :
 - ```*``` non mandatory variable : ```push <t> <n*>``` -> ```n``` parameter can be avoided
 - ```[a, b]``` value between __a__ and __b__ included : ```byte <b>``` with b [0, 3] -> ```byte 0```, ```byte 1```, ```byte 2```, ```byte 3```
 - ```{a, b, c}``` value can be __a__, __b__ or __c__ : ```push <t>``` with t {word, dword} -> ```push word``` or ```push dword```
 - ```...{v}...``` value __v__ is pasted next to the neighbour characters : ```push_{t}_0``` with ```t = word``` -> ```push_word_0```