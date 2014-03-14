/*
-----------------------------------------------------------------------
Copyright 2012 iMinds-Vision Lab, University of Antwerp

Contact: astra@ua.ac.be
Website: http://astra.ua.ac.be


This file is part of the
All Scale Tomographic Reconstruction Antwerp Toolbox ("ASTRA Toolbox").

The ASTRA Toolbox is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The ASTRA Toolbox is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with the ASTRA Toolbox. If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------
$Id$
*/

#include "astra/XMLDocument.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#ifdef _MSC_VER
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#else
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#endif

using namespace rapidxml;
using namespace astra;
using namespace std;



//-----------------------------------------------------------------------------
XMLDocument::XMLDocument() 
{
	fDOMDocument = 0;
}

//-----------------------------------------------------------------------------	
XMLDocument::~XMLDocument() 
{
	delete fDOMDocument;
	//parser->release();
}

//-----------------------------------------------------------------------------
XMLDocument* XMLDocument::readFromFile(string filename) 
{ 
	// create the document
	XMLDocument* res = new XMLDocument();
    res->fDOMDocument = new xml_document<>();

	std::ifstream file(filename.c_str());
	std::stringstream reader;
	reader << file.rdbuf();
	res->fBuf = reader.str();

	res->fDOMDocument->parse<0>((char*)res->fBuf.c_str());

	// return the document
	return res;

}

//-----------------------------------------------------------------------------
// create an XML document with an empty root node
XMLDocument* XMLDocument::createDocument(string sRootName)
{
	XMLDocument* res = new XMLDocument();
	res->fDOMDocument = new xml_document<>();

	char *node_name = res->fDOMDocument->allocate_string(sRootName.c_str());
	xml_node<> *node = res->fDOMDocument->allocate_node(node_element, node_name);

	res->fDOMDocument->append_node(node);

	return res;
}

//-----------------------------------------------------------------------------
XMLNode* XMLDocument::getRootNode() 
{
	// TODO: clean up: this 'new' requires callers to do memory management
	return new XMLNode(fDOMDocument->first_node());
}

//-----------------------------------------------------------------------------
void XMLDocument::saveToFile(string sFilename)
{
	std::ofstream file(sFilename.c_str());

	file << *fDOMDocument;
}

//-----------------------------------------------------------------------------
