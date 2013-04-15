/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2009 Scientific Computing and Imaging Institute,
   University of Utah.

   
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

///////////////////////////
// PORTED SCIRUN v4 CODE //
///////////////////////////

#ifndef CORE_DATATYPES_MESHFACTORY_H
#define CORE_DATATYPES_MESHFACTORY_H 

#include <boost/noncopyable.hpp>
#include <Core/Utils/Singleton.h>
#include <Core/Utils/TypeIDTable.h>
#include <Core/Datatypes/Mesh/FieldFwd.h>
#include <Core/Datatypes/Mesh/MeshTraits.h>
#include <Core/GeometryPrimitives/Point.h>
#include <Core/Datatypes/Mesh/Share.h>

namespace SCIRun {
namespace Core {
namespace Datatypes {

  struct SCISHARE MeshConstructionParameters
  {
    MeshTraits::size_type x_, y_, z_;
    Geometry::Point min_, max_;

    MeshConstructionParameters(MeshTraits::size_type x, MeshTraits::size_type y, MeshTraits::size_type z, const Geometry::Point& min, const Geometry::Point& max);
  };

  typedef MeshHandle5 (*MeshDefaultConstructor)();
  typedef MeshHandle5 (*MeshConstructor)(const MeshConstructionParameters&);

  //TODO: yucky double-singleton to separate registration from construction.

  class SCISHARE MeshFactory : boost::noncopyable
  {
    CORE_SINGLETON( MeshFactory );

  public:
    MeshHandle5 CreateMesh(const Field5Information& info, const MeshConstructionParameters& params);
    MeshHandle5 CreateMesh(const Field5Information& info);
    MeshHandle5 CreateMesh(const std::string& type);

  private:
    MeshFactory();
    MeshHandle5 CreateMesh(const std::string& type, const MeshConstructionParameters& params);
    class MeshRegistry& registry_;
  };

  class SCISHARE MeshRegistry : boost::noncopyable
  {
    CORE_SINGLETON( MeshRegistry );
  public:

    struct SCISHARE MeshTypeID
    {
      MeshTypeID();
      MeshTypeID(const std::string& type, MeshDefaultConstructor defCtor, MeshConstructor ctor = 0);

      std::string type_;
      MeshDefaultConstructor defCtor_;
      MeshConstructor ctor_;

      bool operator==(const MeshTypeID& other) const;
      bool operator!=(const MeshTypeID& other) const;

      friend class MeshRegistry;
    };

    friend class MeshFactory;
  private:
    MeshRegistry();
    Core::Utility::TypeIDTable<MeshTypeID> meshTypeIdLookup_;
  };

}}}

#endif

