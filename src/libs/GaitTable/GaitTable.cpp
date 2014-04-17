#include "GaitTable.h"


hormodular::GaitTable::GaitTable(const std::string file_path)
{
    //-- Check if the file exists
    this->file_path = file_path;
    std::ifstream file(file_path.c_str());
    if (file.good())
    {
        loadFromFile(file_path);
    }
    else
    {
        std::cerr << "[GaitTable] File \"" << file_path << "\" does not exist" << std::endl;
    }
}

int hormodular::GaitTable::loadFromFile( const std::string file_path)
{
    //! \TODO change this temporary code to something more permanent

    //--Variables to store:
    int rows = 0, cols = 0;               //-- Matrix dimensions
    static const int BUFFER_SIZE = 32;    //-- Characters to store in number

    char ch;                       //-- Current character read
    char number[BUFFER_SIZE];	   //-- Number stored as characters

    std::vector<double> data_tmp;	   //-- Vector containing data


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

        //-- Save data on table
        num_parameters = cols-1;

        //-- Add the data to the table
        data.clear();
        ids.clear();

        for (int i = 0; i < rows; i ++)
        {
            ids.push_back( (unsigned long) data_tmp[i*cols]);

            std::vector<float> newRow;
            for (int j = 1; j < cols; j++)
                newRow.push_back(data_tmp[i*cols+j]);
            data.push_back(newRow);
        }

        //-- Just debug
//        std::cout << "[Debug] Data loaded from table: " << std::endl;
//          for (int i = 0; i < rows; i ++)
//          {
//              std::cout << ids[i] << " ";
//              for (int j = 0; j < cols-1; j++)
//                  std::cout << data[i][j] << " ";
//              std::cout << std::endl;
//          }

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
float hormodular::GaitTable::at(int id, int parameter)
{
    int tableRow = lookForID(id);

    if ( tableRow == -1)
    {
        std::cerr << "[GaitTable] Error: ID not found on gait table." << std::endl;
        return 0;
    }

    return data[tableRow][parameter];
}

//-- Get all parameters of a certain id
std::vector<float> hormodular::GaitTable::getParameters(int id)
{
    int tableRow = lookForID(id);

    if ( tableRow == -1)
    {
        std::cerr << "[GaitTable] Error: ID not found on gait table." << std::endl;
        std::vector<float> vector_of_zeroes;

        for (int i = 0; i < num_parameters; i++)
            vector_of_zeroes.push_back(0);

        return vector_of_zeroes;
    }

    return data[tableRow];
}

std::vector<float> hormodular::GaitTable::operator[](int id)
{
    return getParameters(id);
}

int hormodular::GaitTable::getNumParameters()
{
    return num_parameters;
}

std::vector<unsigned long> hormodular::GaitTable::getIDs()
{
    return ids;
}


int hormodular::GaitTable::reload()
{
    return loadFromFile(file_path);
}

int hormodular::GaitTable::lookForID(unsigned long id)
{
    for (int i = 0; i <(int) ids.size(); i++)
        if ( ids[i] == id )
           return i;

    return -1;
}

//-- Save file
//---------------------------------------------------------------------------------------
void hormodular::GaitTable::saveToFile(const std::string file_path)
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
