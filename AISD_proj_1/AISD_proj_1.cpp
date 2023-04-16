#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "List.h"

using namespace std;

void SearchList(String* commands, List* list);

int main()
{
    List list;
    char ch;
    String temp;
    bool block = false;
    bool attribute = true;
    bool false_white_space = false;
    bool false_white_space_sel = true;
    bool add_attr_or_val = true;
    bool space = false;
    bool new_block = true;
    int question_mark = 0;
    int star = 0;
    bool commands = false;
    //to commands
    String command[3];
    int i = -1;
    while ((ch = getchar()) != EOF) {
        if (question_mark == 4) {
            commands = true;
            question_mark = 0;
            i = 0;
            continue;
        }
        else if (ch == '?' && i == -1) {
            question_mark++;
            continue;
        }
        if (star == 4 && commands == true) {
            commands = false;
            star = 0;
            i = -1;
        }
        else if (ch == '*' && i != 2 && commands == true) {
            star++;
            continue;
        }
        if (commands == false) {
            if (block == false) { //poza blokiem
                if (ch == '{' && temp.getSize() == 0) {
                    if (new_block == true) {
                        list.append();
                        new_block = false;
                    }
                    block = true;
                    temp = String();
                    false_white_space_sel = true;
                    space = false;
                }
                else if (ch == '{') {
                    list.append_elem(temp, 's');
                    block = true;
                    temp = String();
                    false_white_space_sel = true;
                    space = false;
                }
                else if (ch == ',') {
                    list.append_elem(temp, 's');
                    temp = String();
                    false_white_space_sel = true;
                    space = false;
                }
                else if (ch == ' ' && false_white_space_sel == true) {
                    continue;
                }
                else if (ch == ' ' && false_white_space_sel == false) {
                    space = true;
                }
                else if (ch == '\t' || ch == '\n') {
                    false_white_space_sel = true;
                    space = false;
                }
                else {
                    if (new_block == true) {
                        list.append();
                        new_block = false;
                    }
                    if (space == true)
                        temp += ' ';
                    temp += ch;
                    false_white_space_sel = false;
                    space = false;
                }
            }
            else {//w bloku
                if (false_white_space == true && (ch == ' ' || ch == '\t' || ch == '\n')) continue;
                else if (false_white_space == true) false_white_space = false;

                if (ch == ':') {
                    attribute = false;
                    false_white_space = true;
                    list.append_elem(temp, 'a');
                    temp = String();
                }
                else if (ch == ';') {
                    attribute = true;
                    list.append_elem(temp, 'v');
                    temp = String();
                }
                else if (ch == '}' && attribute == false) {
                    attribute = true;
                    list.append_elem(temp, 'v');
                    temp = String();
                    block = false;
                    new_block = true;
                }
                else if (ch == '}' && attribute == true) {
                    block = false;
                    new_block = true;
                }
                else if (attribute == true && (ch == ' ' || ch == '\t' || ch == '\n')) continue;
                else if (ch == '\n' && attribute == false) {
                    attribute = true;
                    list.append_elem(temp, 'v');
                    temp = String();
                }
                else
                    temp += ch;
            }
        }
        else {
            if (ch == ',') i++;
            else if (ch == '\n') {
                i = 0;
                SearchList(command, &list);
                command[0] = String();
                command[1] = String();
                command[2] = String();
            }
            else if (ch == '?' && i == 0) {
                command[0] = "?";
                command[1] = ";";
                command[2] = ";";
            }
            else command[i] += ch;
            if (i > 2) {
                command[0] = String();
                command[1] = String();
                command[2] = String();
                while (ch != '\n') {
                    ch = getchar();
                }
                i = 0;
            }
        }
    }
    if (command[0].getSize() != 0)
        SearchList(command, &list);
    return 0;
}

void SearchList(String* commands, List* list) {
    char ch = commands[1][0];
    if (commands[0] == "?") {
        int i = list->HowMany();
        cout << "? == " << i << endl;
    }
    else if (ch == 'E') {
        String temp = list->search_value(commands[0], commands[2]);
        if (temp != ";")
            cout << commands[0] << "," << commands[1] << "," << commands[2] << " == " << temp << endl;
    }
    else if (ch == 'D') {
        if (commands[2][0] == '*') {
            if(list->remove(commands[0].string_to_int()))
                cout << commands[0] << "," << commands[1] << "," << commands[2] << " == deleted" << endl;
        }
        else {
            if(list->remove(commands[0].string_to_int(), commands[2]))
                cout << commands[0] << "," << commands[1] << "," << commands[2] << " == deleted" << endl;
        }
    }
    else {
        if (commands[2] == "?") {
            int number = commands[0].string_to_int();
            if (number != -1) {
                if (list->HowManyInSection(number, ch) != -1)
                    cout << commands[0] << "," << commands[1] << "," << commands[2] << " == " << list->HowManyInSection(number, ch) << endl;
            }
            else {
                cout << commands[0] << "," << commands[1] << "," << commands[2] << " == " << list->HowManyElem(commands[0], ch) << endl;
            }
        }
        else {
            if (ch == 'S') {
                if (list->SelInSection(commands[0].string_to_int(), commands[2].string_to_int()) != ";") {
                    cout << commands[0] << "," << commands[1] << "," << commands[2] << " == ";
                    cout << list->SelInSection(commands[0].string_to_int(), commands[2].string_to_int()) << endl;
                }
            }
            else if (ch == 'A') {
                if (list->AttrInSection(commands[0].string_to_int(), commands[2]) != ";") {
                    cout << commands[0] << "," << commands[1] << "," << commands[2] << " == ";
                    cout << list->AttrInSection(commands[0].string_to_int(), commands[2]) << endl;
                }
            }
        }
    }
}