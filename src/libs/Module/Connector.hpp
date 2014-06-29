//------------------------------------------------------------------------------
//-- Connector
//------------------------------------------------------------------------------
//--
//-- Device that connects different modules for communications
//--
//------------------------------------------------------------------------------
//--
//-- This file belongs to the Hormodular project
//-- (https://github.com/David-Estevez/hormodular.git)
//--
//------------------------------------------------------------------------------
//-- Author: David Estevez-Fernandez
//--
//-- Released under the GPL license (more info on LICENSE.txt file)
//------------------------------------------------------------------------------

/*! \file Connector.hpp
 *  \brief Device that connects different modules for communications
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <vector>
#include "Hormone.hpp"

namespace hormodular {

/*!
 *  \class Connector
 *  \brief Device that connects different modules for communications
 */

class Connector
{
    public:
        Connector();

        /*!
         * \brief Connects a remote connector to this connector
         * \param remoteConnector Connector with is going to be attached to this connector
         * \return True if completed successfully, false otherwise
         */
        bool connectTo( Connector * remoteConnector);

        /*!
         * \brief Send the hormones in the output buffer to their destination modules
         * \return True if completed successfully, false otherwise
         */
        bool sendHormones();

        /*!
         * \brief Adds a Hormone to the output buffer
         * \param outputHormone Hormone to be added to the output buffer
         * \return True if completed successfully, false otherwise
         */
        bool addOutputHormone(Hormone outputHormone);

        /*!
         * \brief Deletes all the hormones stored in the input buffer
         * \return True if completed successfully, false otherwise
         */
        bool clearInputBuffer();



        /*!
         * \brief Returns the local orientation of the connector with respect to the connected module
         * \deprecated This function is no longer used
         */
        int getLocalOrientation() const;

        /*!
         * \brief Sets the local orientation of the connector with respect to the connected module
         * \deprecated This function is no longer used
         */
        void setLocalOrientation(int localOrientation);


        //! \brief Returns the hormones in the input buffer
        std::vector<Hormone> getInputBuffer();

        //! \brief Returns a pointer to the remote connector
        Connector * getRemoteConnector();

   private:
        std::vector<Hormone> inputBuffer;
        std::vector<Hormone> outputBuffer;

        Connector * remoteConnector;
        int localOrientation;

        bool addInputHormone(Hormone inputHormone );
};

}
#endif //-- CONNECTOR_H
