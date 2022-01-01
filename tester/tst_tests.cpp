#include <QtTest>
#include <QCoreApplication>
#include <QVector>
// add necessary includes here
#include"E:\Projects\New\Plotter\validate.h"
#include"E:\Projects\New\Plotter\postfix_evaluate.h"
class Tests : public QObject
{
    Q_OBJECT

public:
    Tests();
    ~Tests();

private slots:
    void evaluate_test();
    void validate_test();
};

Tests::Tests()
{

}

Tests::~Tests()
{

}



void Tests::evaluate_test()
{
    QCOMPARE(evaluate(postfix("x^2+2*x+2") , 2) , 10);
    QCOMPARE(evaluate(postfix("2/x+2*x+x-3") , 4) , 9.5);
    QCOMPARE(evaluate(postfix("x^3^x+2*x/1+2*x") , 3) , 7625597484999);
    QCOMPARE(evaluate(postfix("2*(2+x/2)+x*3^x") , 11) , 1948632);
    QCOMPARE(evaluate(postfix("2.5*x+2/x+3") , 4) , 13.5);

}


void Tests::validate_test()
{
    QVector<QString> errors;
    QCOMPARE(!validate("2.1*x+1/3.5+3^x+12").size() , 1);
    errors.push_back("Invalid character 'x' at index 2.");
    QCOMPARE(validate("2x+1.2") , errors);
    errors.clear();
    errors.push_back("Invalid division by zero at index 7.");
    QCOMPARE(validate("x+2*x/0+3") , errors);
    errors.clear();
    errors.push_back("Invalid end for the expression.");
    QCOMPARE(validate("3*x+2*x+q") , errors);


}








QTEST_MAIN(Tests)

#include "tst_tests.moc"
