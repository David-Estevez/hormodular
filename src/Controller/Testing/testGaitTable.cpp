#include "GaitTable.h"
#include "assert.h"
#include <iostream>
#include <string>

int main(void)
{
    static const uint8_t N_MODULES = 3;
    static const uint8_t N_PARAM = 3;
    static const std::string FILEPATH = "./test_gaittable_file.txt";

    //-- Testing gait table (empty)
    //-------------------------------------------------------------------
    std::cout << "Testing Gait Table (Empty)" << std::endl;
    //-- Create table:
    std::cout << "\tCreating empty table..." << std::endl;
    GaitTable emptyGaitTable( N_MODULES, N_PARAM);

    //-- Check dimensions
    std::cout << "\tChecking dimensions..." << std::endl;
    assert( emptyGaitTable.getNModules() == N_MODULES);
    assert( emptyGaitTable.getNParameters() == N_PARAM);

    //-- Check contents
    std::cout << "\tChecking contents..." << std::endl;
    for (int i = 0; i < emptyGaitTable.getNModules(); i++)
	for ( int j = 0; j < emptyGaitTable.getNParameters(); j++)
	    assert( emptyGaitTable.at(i, j) == 0);

    //-- Check table write / read
    std::cout << "\tTesting write..." << std::endl;
    emptyGaitTable.set(0, 0, 3.1415);
    assert( emptyGaitTable.at(0,0) - 3.1415 < 0.00001 && emptyGaitTable.at(0,0) - 3.1415 > -0.00001);

    //-- Check saving to a file
    std::cout << "\tTesting saving to a file..." << std::endl;
    for (int i = 0; i < emptyGaitTable.getNModules(); i++)
        for ( int j = 0; j < emptyGaitTable.getNParameters(); j++)
            emptyGaitTable.set( i, j, i*emptyGaitTable.getNParameters()+j);

    emptyGaitTable.saveToFile( FILEPATH );

    //-- Checking creating a table from file:
    std::cout << "\tTesting gait table creation from file"  << std::endl;
    GaitTable fileGaitTable( FILEPATH );

    for (int i = 0; i < fileGaitTable.getNModules(); i++)
        for ( int j = 0; j < fileGaitTable.getNParameters(); j++)
            assert( fileGaitTable.at(i, j) == i*emptyGaitTable.getNParameters()+j );

    std::cout << "Gait Table test finished correctly!" << std::endl << std::endl;

    return 0;

}
