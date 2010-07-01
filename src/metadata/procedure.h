/*
  Copyright (c) 2004-2010 The FlameRobin Development Team

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


  $Id$

*/

#ifndef FR_PROCEDURE_H
#define FR_PROCEDURE_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include "metadata/metadataitem.h"
#include "metadata/parameter.h"
#include "metadata/privilege.h"

typedef boost::shared_ptr<Parameter> SharedParameterPtr;
typedef std::vector<SharedParameterPtr> ProcedureParameters;
//-----------------------------------------------------------------------------
class Procedure : public MetadataItem
{
private:
    std::vector<Privilege> privilegesM;
    ProcedureParameters parametersM;
protected:
    virtual void loadChildren();
    virtual void lockChildren();
    virtual void unlockChildren();
public:
    Procedure();

    wxString getCreateSqlTemplate() const;   // overrides MetadataItem::getCreateSqlTemplate()

    bool getChildren(std::vector<MetadataItem *>& temp);

    wxString getExecuteStatement();

    ProcedureParameters::iterator begin();
    ProcedureParameters::iterator end();
    ProcedureParameters::const_iterator begin() const;
    ProcedureParameters::const_iterator end() const;

    size_t getParamCount() const;
    SharedParameterPtr findParameter(const wxString& name) const;

    wxString getOwner();
    wxString getSource();
    wxString getAlterSql(bool full = true);
    wxString getDefinition();   // used for calltip in sql editor
    std::vector<Privilege>* getPrivileges();

    void checkDependentProcedures();

    virtual const wxString getTypeName() const;
    virtual void acceptVisitor(MetadataItemVisitor* visitor);
};
//-----------------------------------------------------------------------------
#endif
