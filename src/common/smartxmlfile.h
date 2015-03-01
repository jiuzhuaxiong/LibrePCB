/*
 * EDA4U - Professional EDA for everyone!
 * Copyright (C) 2013 Urban Bruhin
 * http://eda4u.ubruhin.ch/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SMARTXMLFILE_H
#define SMARTXMLFILE_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include "smartfile.h"

/*****************************************************************************************
 *  Forward Declarations
 ****************************************************************************************/

class XmlDomDocument;

/*****************************************************************************************
 *  Class SmartXmlFile
 ****************************************************************************************/

/**
 * @brief The SmartXmlFile class represents a XML file and provides methods to load/save
 *        XML DOM trees (#XmlDomDocument)
 *
 * With #parseFileAndBuildDomTree() the XML file can be parsed and a DOM tree is created.
 * With #save() the DOM tree can be saved back to the XML file.
 *
 * @note See class #SmartFile for more information.
 *
 * @author ubruhin
 * @date 2014-08-13
 */
class SmartXmlFile final : public SmartFile
{
        Q_OBJECT

    public:

        // Constructors / Destructor

        /**
         * @brief The constructor to open an existing XML file
         *
         * This constructor tries to open an existing file and throws an exception if an
         * error occurs.
         *
         * @param filepath  See SmartFile#SmartFile()
         * @param restore   See SmartFile#SmartFile()
         * @param readOnly  See SmartFile#SmartFile()
         *
         * @throw Exception If the specified text file could not be opened successful, an
         *                  exception will be thrown.
         */
        SmartXmlFile(const FilePath& filepath, bool restore, bool readOnly) throw (Exception) :
            SmartXmlFile(filepath, restore, readOnly, false) {}

        /**
         * @copydoc SmartFile#~SmartFile()
         */
        ~SmartXmlFile() noexcept;


        // General Methods

        /**
         * @brief Open and parse the XML file and build the whole DOM tree
         *
         * @return  A pointer to the created DOM tree. The caller takes the ownership of
         *          the DOM document.
         */
        QSharedPointer<XmlDomDocument> parseFileAndBuildDomTree() const throw (Exception);

        /**
         * @brief Write the XML DOM tree to the file system
         *
         * @param domDocument   The DOM document to save
         * @param toOriginal    Specifies whether the original or the backup file should
         *                      be overwritten/created.
         *
         * @throw Exception If an error occurs
         */
        void save(const XmlDomDocument& domDocument, bool toOriginal) throw (Exception);


        // Static Methods

        /**
         * @brief Create a new XML file
         *
         * @note    This method will NOT immediately create the file! The file will be
         *          created after calling #save().
         *
         * @param filepath  The filepath to the file to create (always to the original file,
         *                  not to the backup file with "~" at the end of the filename!)
         *
         * @return The #SmartXmlFile object of the created file
         *
         * @throw Exception If an error occurs
         */
        static SmartXmlFile* create(const FilePath &filepath) throw (Exception);


    private:

        // make some methods inaccessible...
        SmartXmlFile();
        SmartXmlFile(const SmartXmlFile& other);
        SmartXmlFile& operator=(const SmartXmlFile& rhs);


        // Private Methods

        /**
         * @brief Constructor to create or open a XML file
         *
         * @param filepath          See SmartFile#SmartFile()
         * @param restore           See SmartFile#SmartFile()
         * @param readOnly          See SmartFile#SmartFile()
         * @param create            See SmartFile#SmartFile()
         *
         * @throw Exception See SmartFile#SmartFile()
         */
        SmartXmlFile(const FilePath& filepath, bool restore, bool readOnly, bool create) throw (Exception);

};

#endif // SMARTXMLFILE_H