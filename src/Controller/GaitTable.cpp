#include "GaitTable.h"

//-- Constructors & destructors
//----------------------------------------------------------------------------------------

//-- Create an empty gait table:
GaitTable::GaitTable(uint8_t n_modules, uint8_t n_parameters)
{
    //-- Set parameters:
    this->n_modules = n_modules;
    this->n_parameters = n_parameters;

    //-- Allocate memory for the table:
    this->data = new float[ n_modules * n_parameters];

    //-- Initialize the empty gait table:
    for (int i = 0; i < n_modules * n_parameters; i++)
    {
    *(this->data + i) = 0;
    }
}

//-- Create a gait table from a octave file:
GaitTable::GaitTable(const std::string file_path)
{
    this->data = NULL;
    this->loadFromFile( file_path);
}

//-- Free the memory
GaitTable::~GaitTable()
{
    delete[] data;
}

int GaitTable::loadFromFile( const std::string file_path)
{
    //! \TODO change this temporary code to something more permanent

    //--Variables to store:
    int rows = 0, cols = 0;               //-- Matrix dimensions
    static const int BUFFER_SIZE = 32;    //-- Characters to store in number

    char ch;                       //-- Current character read
    char number[BUFFER_SIZE];	   //-- Number stored as characters

    std::vector<float> data_tmp;	   //-- Vector containing data


    //-- Open the file
    std::ifstream input_file( file_path.c_str() );

    if (input_file.is_open())
    {
        //-- Erase the buffer:
        for (int i = 0; i < BUFFER_SIZE; i++)
            number[i] = '\0';

        //-- Extracting data from file:
        while (!input_file.eof())
        {
            input_file.get(ch);  	//-- Get a character

            //-- Ignore comments
            if (ch == '#')
            {
                //-- Ignore data until next line:
                while( !input_file.eof() && ch != '\n')
                    input_file.get(ch);

                continue;
            }

            //-- Check if it is a number:
            if (ch == '-')
            {
                //-- Read next character:
                input_file.get(ch);

                //-- For Negative numbers:
                if ( ch >= '0' && ch <= '9' )
                {
                    number[0] = '-';
                    number[1] = ch;

                    int i = 2;

                    //-- Store the number in 'number'
                    while( !input_file.eof() && ch != '\n' && ch != ' ' && i < BUFFER_SIZE)
                    {
                        input_file.get(ch);
                        if ( ( ch >= '0' && ch <= '9' ) || ch == 'e' || ch == '.' || ch == '-')
                            number[i] = ch;
                        i++;
                    }

                    //-- Convert the string to a double and store it in vector 'data'
                    data_tmp.push_back( atof(number) );

                    //-- Erase the buffer:
                    for (int i = 0; i < BUFFER_SIZE; i++)
                        number[i] = '\0';
                }
            }
            else
            {
                //-- For positive numbers:
                if ( ch >= '0' && ch <= '9' )
                {
                    number[0] = ch;

                    int i = 1;

                    //-- Store the number in 'number'
                    while( !input_file.eof() && ch != '\n' && ch != ' ' && i < BUFFER_SIZE)
                    {
                        input_file.get(ch);
                        if ( ( ch >= '0' && ch <= '9' ) || ch == 'e' || ch == '.' || ch == '-')
                            number[i] = ch;
                        i++;
                    }

                    //-- Convert the string to a double and store it in vector 'data'
                    data_tmp.push_back( atof(number) );

                    //-- Erase the buffer:
                    for (int i = 0; i < BUFFER_SIZE; i++)
                        number[i] = '\0';
                }
            }

            //-- New line detection / number of columns
            if (ch == '\n' && !input_file.eof())
            {
                //-- For first row
                if ( rows == 0)
                    cols = data_tmp.size(); //-- Obtain the number of columns

                rows++;
            }
        }

        //-- Close the file:
        input_file.close();


        /* You can keep this */
        //-- Set parameters:
        this->n_modules = rows;
        this->n_parameters = cols;

        //-- Allocate memory for the table:
        delete[] this->data;
        this->data = NULL;

        this->data = new float[ n_modules * n_parameters];

        //-- Initialize the empty gait table:
        for (int i = 0; i < n_modules * n_parameters; i++)
            *(this->data+i) = 0;

        //-- Add the data to the table
        for (int i = 0; i < n_modules; i ++)
            for (int j = 0; j < n_parameters; j++)
                this->set(i, j, data_tmp[i*cols+j]);

    }
    else
    {
        //-- Show error message
        std::cerr <<"[GaitTable] Error: File " << file_path << " could not be opened!" << std::endl;
        return -1;
    }

    return 0;
}





//-- Get things
//----------------------------------------------------------------------------------------
//-- Get element of the gait table
float GaitTable::at(uint8_t id, uint8_t parameter)
{
    return *(data + id * n_parameters + parameter);
}

//-- Get all parameters of a certain id
float * GaitTable::getParameters( uint8_t id)
{
    return data + id*n_parameters;
}

//-- Get number of modules
uint8_t GaitTable::getNModules()    { return n_modules; }
uint8_t GaitTable::getNParameters() { return n_parameters; }

//-- Set things
//---------------------------------------------------------------------------------------
void GaitTable::set(uint8_t id, uint8_t parameter, float value)
{
    *(data + id * n_parameters + parameter) = value;
}

//-- Save file
//---------------------------------------------------------------------------------------
void GaitTable::saveToFile(const std::string file_path)
{
    //-- Open file
    std::ofstream output_file( file_path.c_str() );

    //-- Check file
    if ( output_file.is_open() )
    {
        //-- Print file header:
        output_file << "# Gait Table created by Hormodular [https://github.com/David-Estevez/hormodular.git]"
                 << std::endl;

        output_file << "# name: gaitTable" << std::endl;
        output_file << "# type: matrix" << std::endl;
        output_file << "# rows: " << (int) n_modules << std::endl;
        output_file << "# columns: " << (int) n_parameters << std::endl;

        //-- Print actual data of the gait table
        for ( int i = 0; i < n_modules; i++)
        {
            for ( int j = 0; j < n_parameters ; j ++)
                output_file << this->at( i, j ) << " ";

            output_file << std::endl;
        }

        output_file.close();
    }
    else
    {
        std::cerr << "[GaitTable] Error: file " << file_path << " could not be opened." << std::endl;
    }
}
