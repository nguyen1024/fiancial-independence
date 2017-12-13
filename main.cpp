#include <QCoreApplication>
#include <QDateTime>
#include <iostream>

/** ***********************************************************************************************
 *
 *
 *
 *************************************************************************************************/

typedef struct a_t
{
    double contribution;
    double interestRate;
    double amount;
    double withdrawalRate;
    double withdrawalAmountGoal;
    long   iterations;

    QDateTime startDate;

    a_t()
    {
        contribution         = 0.0;
        interestRate         = 0.0;
        amount               = 0.0;
        withdrawalRate       = 0.0;
        withdrawalAmountGoal = 0.0;
        iterations           = 0;
    }
} a_t;

typedef struct b_t
{
    QDateTime endDate;
    double amount;

    b_t()
    {
        amount = 0.0;
    }
} b_t;

/** ***********************************************************************************************
 *
 * Try less processor intensive algorithm.
 *
 * To get months in between, count the number of times you reach the end of the month.
 *
 *************************************************************************************************/

void calc( const a_t& a, b_t& b )
{
    b.endDate = a.startDate;
    b.amount = a.amount;

    // For each iteration ...
    for( int i = 0; i < a.iterations; ++i )
    {
        // Add contribution.
        //b.amount += a.contribution / double( b.endDate.date().daysInMonth() ); // days
        b.amount += a.contribution / double( b.endDate.date().daysInMonth() * 24.0 ); // hours
        //b.amount += a.contribution / double( b.endDate.date().daysInMonth() * 24.0 * 60.0 ); // minutes

        // Add interest.
        //b.amount += b.amount * a.interestRate / double( b.endDate.date().daysInYear() ); // days
        b.amount += b.amount * a.interestRate / double( b.endDate.date().daysInYear() * 24.0 ); // hours
        //b.amount += b.amount * a.interestRate / double( b.endDate.date().daysInYear() * 24.0 * 60.0 ); // minutes

        // Check whether to stop.
        if( a.withdrawalAmountGoal <= ( b.amount * a.withdrawalRate ) )
        {
            std::cout << "(dateTime:(" << b.endDate.toString( "dd.MM.yyyy hh:mmap" ).toStdString() << ") newAmount:" << b.amount << ")" << std::endl;
            break;
        }

        // Increment time.
        //b.endDate = b.endDate.addDays( 1 ); // days
        b.endDate = b.endDate.addSecs( 60.0 * 60.0 ); // hours
        //b.endDate = b.endDate.addSecs( 60.0 ); // minutes
    }
}

/** ***********************************************************************************************
 *
 * Entry Point
 *
 *************************************************************************************************/

int main( int argc, char *argv[] )
{
    //QCoreApplication a( argc, argv );

    a_t a;
    //a.startDate = QDateTime( QDate( 2017, 12, 14 ) );
    a.startDate = QDateTime::currentDateTime();
    a.contribution = 3000.0;
    a.interestRate = 0.07;
    a.amount = 60486.73;
    a.withdrawalRate = 0.04;
    a.withdrawalAmountGoal = 24000.0;
    a.iterations = 1000000 * 10;
    //a.iterations = 1440;
    //a.iterations = 2;

    // Error check. Ensure date is valid.
    if( !(a.startDate.isValid() ) )
    {
        EXIT_FAILURE;
    }

    b_t b;

    calc( a, b );
    QDateTime dateOne = b.endDate;

    a.interestRate = 0.08;
    //a.amount += 10000.0;
    //a.contribution += 100.0;
    calc( a, b );

    std::cout << "(deltaDays:" << dateOne.daysTo( b.endDate ) << ")" << std::endl;
    std::cout << "(deltaHours:" << dateOne.secsTo( b.endDate ) / 60.0 / 60.0 << ")" << std::endl;
    std::cout << "(deltaMinutes:" << dateOne.secsTo( b.endDate ) / 60.0 << ")" << std::endl;
    std::cout << "(deltaSeconds:" << dateOne.secsTo( b.endDate ) << ")" << std::endl;

    //return a.exec();
}
