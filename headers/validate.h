#ifndef VALIDATE_H
#define VALIDATE_H
#include <QString>
#include <QVector>
#include <QChar>
#include <QStack>

QVector<QString> validate(QString s){
    int size = s.size();
    bool dot_flag = 1;
    QVector<QString> errors;
    if(size == 0){
         errors.push_back("Empty Expression.");
         return errors;
    }
    if(size == 1 && !s[size-1].isDigit() && s[size-1] != 'x'){
         errors.push_back("Please insert at least one operand.");
         return errors;
    }
    if(!s[0].isDigit() && s[0] != 'x' && s[0] != '-' && s[0] != '('){
         errors.push_back("Inavlid begin for the expression.");
    }
    if(!s[size-1].isDigit() && s[size-1] != 'x' && s[size-1] != ')' ){
          errors.push_back("Invalid end for the expression.");
          return errors;
    }

    QStack <QChar> balance;
    for (int i = 0; i < size; i++)
    {
          if(s[i] == '('){
              balance.push(s[i]);
          }
          else if(s[i] == ')'){
              if(balance.empty()) errors.push_back("')' is not opened.");
              else balance.pop();
          }
    }
    if (!balance.empty()) errors.push_back("'(' is not closed.");

    for (int i = 0; i < size-1; i++)
    {
        if(s[i] == '+' ||  s[i] == '-' ||  s[i] == '*' ||  s[i] == '/' ||  s[i] == '^') dot_flag =1;
        if(s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '^' &&
           s[i] != '(' && s[i] != ')' && !s[i].isDigit() && s[i] != 'x' && s[i] != '.' ) {
            errors.push_back("Invalid character '" + QString(1 , s[i]) + QString(1 , '\'')
                             + " at index " + QString::number(i+1) + QString(1 , '.') );
            continue;
        }

        else if((s[i] == '+' ||  s[i] == '-') && (s[i+1].isDigit() || s[i+1] == 'x' || s[i+1] == '(')) {
            dot_flag = 1;
            continue;
        }
        else if(s[i] == '/' && s[i+1] == '0' && ((i+2 < s.size() && s[i+2] != '.') || i+1 == s.size()-1)){
            errors.push_back("Invalid division by zero at index " + QString::number(i+2) + ".");
            i++;
        }
        else if((s[i] == '*' ||  s[i] == '/' || s[i] == '^')  && (s[i+1].isDigit() || s[i+1] == 'x' ||
                 s[i+1] == '(' || s[i+1] == '-')) {
            dot_flag = 1;
            continue;
        }
        else if(s[i] == '(' && (s[i+1].isDigit() || s[i+1] == 'x' || s[i+1] == '(' || s[i+1] == '-')) continue;
        else if(s[i] == ')' && (s[i+1] == '+' || s[i+1] == '-' || s[i+1] == '*' || s[i+1] == '/' ||
                s[i+1] == '^' || s[i+1] == ')' )) continue;
        else if(s[i].isDigit() && (s[i+1].isDigit() || s[i+1] == '+' || s[i+1] == '-' ||
                s[i+1] == '*' || s[i+1] == '/' || s[i+1] == '^' || s[i+1] == ')' ||
                                   (s[i+1] == '.' && dot_flag ))) continue;
        else if(s[i] == '.' && s[i+1].isDigit()){
            dot_flag = 0;
             continue;
        }
        else if(s[i] == 'x' && (s[i+1] == '+' || s[i+1] == '-' || s[i+1] == '*' || s[i+1] == '/' ||
                                s[i+1] == '^' || s[i+1] == ')' )) continue;
        else {
            errors.push_back("Invalid character '" + QString(1 , s[i+1])
                    + QString(1 , '\'') + " at index " + QString::number(i+2) + QString(1 , '.') );
            i++;
        }

    }
    return errors;


}
#endif // VALIDATE_H
