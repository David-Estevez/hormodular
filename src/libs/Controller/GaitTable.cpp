#include "GaitTable.h"


GaitTable::GaitTable(const std::string file_path, const int num_parameters )
{
    //-- Set parameters:
    this->num_parameters = num_parameters;

    //-- Check if the file exists
    this->file_path = file_path;
    std::ifstream file(file_path.c_str());
    if (file.good())
    {
        loadFromFile(file_path);
    }
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

        //-- Check data
        if ( num_parameters != cols -1 )
        {
            std::cerr<<"[GaitTable] Error: data on the file is not consistent with number of parameters."
                    << std::endl;
            return -1;
        }

        //-- Add the data to the table
        data.clear();
        for (int i = 0; i < rows; i ++)
        {
            std::vector<float> newRow;
            for (int j = 0; j < cols; j++)
                newRow.push_back(data_tmp[i*cols+j]);
            data.push_back(newRow);
        }

        //-- Just debug
        std::cout << "[Debug] Data loaded from table: " << std::endl;
        for (int i = 0; i < rows; i ++)
        {
            for (int j = 0; j < cols; j++)
                std::cout << data[i][j] << " ";
            std::cout << std::endl;
        }

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
float GaitTable::at(int id, int parameter)
{
    int tableRow = lookForID(id);

    if ( tableRow == -1)
    {
        std::cerr << "[GaitTable] Error: ID not found on gait table. Creating row..." << std::endl;
        setValue(id, parameter, 0);
        return 0;
    }

    return data[tableRow][parameter+1];
}

//-- Get all parameters of a certain id
std::vector<float> GaitTable::getParameters(int id)
{
    int tableRow = lookForID(id);

    if ( tableRow == -1)
    {
        std::cerr << "[GaitTable] Error: ID not found on gait table. Creating row..." << std::endl;
        setValue(id, 0, 0);
        return this->getParameters(id);
    }

    return data[tableRow];
}

int GaitTable::getNumParameters()
{
    return num_parameters;
}

//-- Set things
//---------------------------------------------------------------------------------------
void GaitTable::setValue(int id, int parameter, float value)
{
    int tableRow = lookForID(id);

    if (tableRow == -1)
    {
        std::cout << "[GaitTable] ID: " << id << " was not found. Creating row for ID..." << std::endl;
        std::vector<float> newRow;
        newRow.push_back(id);

        for (int i=0; i<num_parameters; i++)
            newRow.push_back(0);

        newRow[parameter+1] = value;

        data.push_back(newRow);

        saveToFile(file_path);
    }
    else
    {
        data[tableRow][parameter+1] = value;
        saveToFile(file_path);
    }
}

int GaitTable::setRow(int id, std::vector<float> values)
{
    if ( (int)values.size() != num_parameters )
    {
        std::cerr << "[GaitTable] Error: size of input vector does not match number of parameters ("
                  << values.size() << "!=" << num_parameters << std::endl;
        return -1;
    }

    int tableRow = lookForID(id);

    if (tableRow == -1)
    {
        std::cout << "[GaitTable] ID: " << id << " was not found. Creating row for ID..." << std::endl;

        std::vector<float> newRow;
        newRow.push_back(id);

        for (int i=0; i<(int)values.size(); i++)
            newRow.push_back(values[i]);

        data.push_back(newRow);

        saveToFile(file_path);
        return 0;
    }
    else
    {
        data[tableRow] = values;

        saveToFile(file_path);
        return 0;
    }
}

int GaitTable::reload()
{
    return loadFromFile(file_path);
}

int GaitTable::lookForID(int id)
{
    for (int i = 0; i <(int) data.size(); i++)
        if ( (int) data[i][0] == id )
            return i;

    return -1;
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
        output_file << "# rows: " << data.size() << std::endl;
        output_file << "# columns: " << num_parameters+1 << std::endl;

        //-- Print actual data of the gait table
        for ( int i = 0; i < (int)data.size(); i++)
        {
            for ( int j = 0; j < (int)data[i].size() ; j ++)
                output_file << data[i][j] << " ";

            output_file << std::endl;
        }

        output_file.close();
    }
    else
    {
        std::cerr << "[GaitTable] Error: file " << file_path << " could not be opened." << std::endl;
    }
}
