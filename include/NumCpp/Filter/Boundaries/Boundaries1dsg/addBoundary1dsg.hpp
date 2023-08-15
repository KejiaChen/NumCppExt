/// @file
/// @author David Pilger <dpilger26@gmail.com>
/// [GitHub Repository](https://github.com/dpilger26/NumCpp)
///
/// License
/// Copyright 2018-2023 David Pilger
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this
/// software and associated documentation files(the "Software"), to deal in the Software
/// without restriction, including without limitation the rights to use, copy, modify,
/// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
/// permit persons to whom the Software is furnished to do so, subject to the following
/// conditions :
///
/// The above copyright notice and this permission notice shall be included in all copies
/// or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
/// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
/// PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
/// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
/// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
/// DEALINGS IN THE SOFTWARE.
///
/// Description
/// Wrap boundary
///
#pragma once

#include <string>

#include "NumCpp/Core/Internal/Error.hpp"
#include "NumCpp/Core/Internal/StaticAsserts.hpp"
#include "NumCpp/Core/Types.hpp"
// #include "NumCpp/Filter/Boundaries/Boundaries1d/constant1d.hpp"
// #include "NumCpp/Filter/Boundaries/Boundaries1d/mirror1d.hpp"
// #include "NumCpp/Filter/Boundaries/Boundaries1d/nearest1d.hpp"
#include "NumCpp/Filter/Boundaries/Boundaries1dsg/reflect1dsg.hpp"
// #include "NumCpp/Filter/Boundaries/Boundaries1d/wrap1d.hpp"
// #include "NumCpp/Filter/Boundaries/Boundaries1d/interpolate1d.hpp"
#include "NumCpp/Filter/Boundaries/Boundary.hpp"
#include "NumCpp/NdArray.hpp"

namespace nc::filter::boundary
{
    //============================================================================
    // Method Description:
    /// Wrap boundary
    ///
    /// @param inImage
    /// @param inBoundaryType
    /// @param inKernalSize
    /// @param inConstantValue (default 0)
    /// @return NdArray
    ///
    template<typename dtype>
    NdArray<dtype> addBoundary1dsg(const NdArray<dtype>& inImage,
                                 Boundary              inBoundaryType,
                                 uint32                inKernalSize,
                                 dtype                 inConstantValue = 0)
    {
        STATIC_ASSERT_ARITHMETIC(dtype);

        switch (inBoundaryType)
        {
            case Boundary::REFLECT:
            {   
                const uint32 boundarySize = inKernalSize; // integer division
                return reflect1dsg(inImage, boundarySize);
            }
            case Boundary::CONSTANT:
            {
                const uint32 boundarySize = inKernalSize; // integer division
                return reflect1dsg(inImage, boundarySize);
            }
            case Boundary::NEAREST:
            {   
                const uint32 boundarySize = inKernalSize; // integer division
                // return nearest1d(inImage, boundarySize);
                return reflect1dsg(inImage, boundarySize);
            }
            case Boundary::MIRROR:
            {   
                const uint32 boundarySize = inKernalSize; // integer division
                // return mirror1d(inImage, boundarySize);
                return reflect1dsg(inImage, boundarySize);
            }
            case Boundary::WRAP:
            {   
                const uint32 boundarySize = inKernalSize; // integer division
                // return wrap1d(inImage, boundarySize);
                return reflect1dsg(inImage, boundarySize);
            }
            // case Boundary::INTERPOLATE:
            // {
            //     const uint32 boundarySize = inKernalSize - 1; // integer division
            //     return interpolate1d(inImage, boundarySize);
            // }
            default:
            {
                // This can't actually happen but just adding to get rid of compiler warning
                THROW_INVALID_ARGUMENT_ERROR("ERROR!");
            }
        }

        return NdArray<dtype>(); // get rid of compiler warning
    }
} // namespace nc::filter::boundary
