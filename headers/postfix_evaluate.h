#ifndef POSTFIX_EVALUATE_H
#define POSTFIX_EVALUATE_H
#include <QString>
#include <QVector>
#include <QChar>
#include <QStack>
bool match(QChar s1 , QChar s2){
       if(s1 == s2) return 1;
       else {
           if((s1 == '*' && s2 == '/') || (s1 == '/' && s2 == '*') ) return 1;
           if((s1 == '+' && s2 == '-') || (s1 == '-' && s2 == '+') ) return 1;
           if(s1 == '(' && s2 == ')') return 1;
       }
       return 0;
}
bool is_operator(QChar s){
    if(s == '+' || s == '-' || s == '*' || s == '/' || s == '^' || s == '(') return 1;
    return 0;
}
int get_priority(QChar s){
    if(s == '^') return 1;
    else if(s == '*' || s == '/') return 2;
    else if(s == '+' || s == '-') return 3;
    else if(s == '(') return 5;
    else return -1;
}
QString postfix(QString exp){
    int priority = 0;
    QString post="";
    QStack <QChar> s;
    for (int i = 0; i < exp.size(); i++)
    {
        if((exp[i] >= '0' && exp[i] <= '9') || (exp[i] == 'x') || exp[i] == '.'){
               post += exp[i];
        }
        else if(exp[i] == '-' && i ==0) {
                    s.push('!');
                    priority = 4;
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^'){
                post += " ";
                if(s.size() == 0){
                    s.push(exp[i]);
                    priority = get_priority(exp[i]);
                }
                else{

                          if(exp[i] == '-' && is_operator(exp[i-1])){
                              s.push('!');
                              priority = 4;
                          }
                          else if(s.top() == '!'){
                              post = post + s.top() + " ";
                              s.pop();
                              s.push(exp[i]);
                          }
                          else if(exp[i] == '^' && s.top() == '^'){
                                s.push(exp[i]);
                            }
                          else{
                          while(!s.empty() && get_priority(exp[i]) >= priority){


                              post = post + s.top() + " ";
                              s.pop();
                              if(!s.empty()) priority = get_priority(s.top());

                          }
                          s.push(exp[i]);
                          priority = get_priority(exp[i]);

                          }
                }
        }
        else if(exp[i] == '(' ) {
            s.push(exp[i]);
            priority = get_priority(exp[i]);
        }
        else if(exp[i] == ')'){
                post += " ";
                while(!match(s.top() , exp[i])){
                    post = post + s.top() + " ";
                    s.pop();
                }
                post.remove(post.size()-1 , 1);
                s.pop();
                if(!s.empty()) priority = get_priority(s.top());
        }
    }

    while (!s.empty())
    {
        post = post +  " " +  s.top() ;
        s.pop();
    }


return post;
}

float evaluate(QString post , float x_value){
    QStack <float> s;
    for (int i = 0; i < post.size() ; i++)
    {

        if(post[i] == 'x') {
            s.push(x_value);
            continue;
        }
        else if(post[i] >= '0' && post[i] <= '9' ){
            QString op="";
            while(i < post.size() && !post[i].isSpace()){
                op += post[i];
                i++;

            }
            s.push(op.toFloat());
        }
        else if(post[i] == '!'){
            float temp = -1 * s.top();
            s.pop();
            s.push(temp);
        }
        else if(post[i] == '+'){
            float temp1 = s.top();
            s.pop();
            float temp2 = s.top();
            s.pop();
            float ans = temp1 + temp2;
            s.push(ans);
        }
        else if(post[i] == '-'){
            float temp1 = s.top();
            s.pop();
            float temp2 = s.top();
            s.pop();
            float ans = temp2 - temp1;
            s.push(ans);
        }
        else if(post[i] == '*'){
            float temp1 = s.top();
            s.pop();
            float temp2 = s.top();
            s.pop();
            float ans = temp1 * temp2;
            s.push(ans);
        }
        else if(post[i] == '/'){
            float temp1 = s.top();
            s.pop();
            float temp2 = s.top();
            s.pop();
            float ans = temp2 / temp1;
            s.push(ans);
        }
        else if(post[i] == '^'){
            float temp1 = s.top();
            s.pop();
            float temp2 = s.top();
            s.pop();
            float ans =pow(temp2 , temp1);
            s.push(ans);
        }

    }
   return s.top();
}

#endif // POSTFIX_EVALUATE_H
