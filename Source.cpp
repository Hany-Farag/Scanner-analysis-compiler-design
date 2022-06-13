#include <bits/stdc++.h>
using namespace std;
/*define types of token */
map<string, int> op{
    {"+",1},{"*",1},{"/",1},{"-",1},{"<<",1},{">>",1},
    {"<",1},{">",1},{"<=",1},{">=",1},{"=",1},{"-=",1},{"+=",1},
    {"*=",1},{"/=",1},{"++",1},{"--",1},{"==",1}
};

map<string, int>kd{
    {"int",1},{"double",1},{"float",1},{"int",1},{"return",1},{"do",1},{"for",1},{"while",1}
    ,{"include",1},{"define",1},{"iostream",1},{"endl",1},{"cout",1},{"cin",1},{"std",1 }
};
map<string, int> sepr{ {",",1},{";",1},{"(",1},{")",1},{"{",1},{"}",1},{"[",1},{"]",1},{"'",1},{"\"",1},
{"#",1}
};
map<string, int>comment{ {"//",1},{"/*",1} };
//==================================================================================================================//
string filename = "program.txt";
fstream file(filename, fstream::in);
bool single_comment = false, multi_comment = false;
bool comment_exist(char ch) {
    if (single_comment && ch == '\n')
    {
        //cout << "end of comment" << endl;
        single_comment = false;
        return true;
    }
    else if (multi_comment && ch == '*')
    {
        file >> ch;
        if (ch == EOF)
            return true;
        else
            if (ch == '/')
            {
                multi_comment = false;
                return true;
            }

    }
    if (single_comment || multi_comment)
        return true;
    else
        return false;
}
bool is_litral(string token)
{
    // if token is string literal
    if (token[0] == '"' && token[token.size() - 1] == '"')
        return true;
    //if token is number
    int ok = 0;
    for(auto i:token)
    {
        if ((i >= '0' && i <= '9') || i == '.')
        {
            ok++;
        }
    }
    if (ok ==token.size())return true;
    //if token is true or false 
    if (token == "true" || token == "false")
        return true;
    return false;
}
bool ck_id(string token)
{
    if (!isalpha(token[0])&&token[0]!='_')
    {
       // cout << isalpha(token[0]) << endl;
        return false;
    }
    for (auto i : token)
    {
        if (i == '_' || i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z' || i >= '0' && i <= '9')
            continue;
        return false;
    }
    return true;
}
int cnt = 0;
void ck_stuts(string token)
{
    cout <<"    " << ++cnt << ": ";
    if (op[token])cout << "( " << token << ") -----> operator" << endl;
    else if (comment[token])cout << "( " << token << ") -----> commnet" << endl;
    else if(sepr[token])cout << "( " << token << ") -----> seprator" << endl;
    else if(kd[token])cout << "( " << token << ") -----> keyword" << endl;
    else if(is_litral(token))cout << "( " << token << ") -----> litral" << endl;
    else if(ck_id(token)) cout << "( " << token << ") -----> Id" << endl;
    else 
        cout << "( " << token << ") -----> unknown token" << endl;
    cout << "|==========================================|\n";
}
void get_tokens(string filename)
{
    char ch; string  token = "";
    while (file >> noskipws >> ch)
    {
        if (comment_exist(ch))
        {
             //cout << "yes" << endl;
            continue;
        }

        if (ch == '/')
        {
            string temp = "/";
            file >> ch;
            if (ch == EOF)
                break;
            else if (ch == '/')
            {
                single_comment = true;
                temp += ch;
                ck_stuts (temp);
                continue;
            }
            else if (ch == '*')
            {
                multi_comment = true;
                temp += ch;
                ck_stuts(temp);
                continue;
            }
            else if (ch == '=')
            {
                ck_stuts(temp + ch);
                continue;
            }
            else {
                ck_stuts(temp);
            }
        }
        if (ch == ' ' || ch == '\n')
        {
            if (!token.empty())
            {
                ck_stuts(token);
                token = "";
            }
            continue;
        }
        /*if the ch is operator and the token string store non operator char 
        * you print the type of token string and then clear it to store the current charcter
        * x++;
        * here if we stand in + and token = x then we should print type of (x) then token will be token=+
        */
        if (op[string(1, ch)] && !op[token])
        {
            if (!token.empty())
            {
                ck_stuts(token);
                token = "";
            }
        } 
        /* in this case the token is operator and the ch is not operator
        * so the ch can be /seperator/ so it print type of token 
        * then check if ch is sepr or not 
        * if ch not sepr you just add to token 
        * 
        */
        if (!op[string(1, ch)] && op[token])
        {
            if (!token.empty())
            {
                ck_stuts(token);
                token = "";
            }
        }
        /*
        * if the ch is op and token is also op then 
        * it add ch to token until the ch or token 
        * become not operator
         */
        if (sepr[string(1, ch)])
        {
            if (!token.empty())
            {
                ck_stuts(token);
                token = "";
            }
            ck_stuts(string(1, ch));
            continue;
        }
        token += ch;
    }
    file.close();
}
int main()
{
    get_tokens(filename);
    return 0;
}