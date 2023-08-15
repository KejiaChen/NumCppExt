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
/// Calculates a one-dimensional kernel convolution.
///
#pragma once

#include "NumCpp/Core/Slice.hpp"
#include "NumCpp/Core/Types.hpp"
#include "NumCpp/Functions/dot.hpp"
#include "NumCpp/Functions/fliplr.hpp"
#include "NumCpp/NdArray.hpp"

namespace nc::filter
{
    //============================================================================
    // Method Description:
    /// Calculates a one-dimensional kernel convolution.
    ///
    /// SciPy Reference:
    /// https://docs.scipy.org/doc/scipy/reference/generated/scipy.ndimage.convolve1d.html#scipy.ndimage.convolve1d
    ///
    /// @param inImageArray
    /// @param inWeights
    /// @return NdArray
    ///
    template<typename dtype>
    NdArray<dtype> convolve1drt(const NdArray<dtype>& inImageArray,
                                const NdArray<dtype>& inWeights)
    {   
        uint32 boundarySize;
        uint32 windowSize;
        boundarySize = 0;
        windowSize = inWeights.size();
        NdArray<dtype> arrayWithBoundary = inImageArray; // no padding on the edge
        
        NdArray<dtype> output(1, inImageArray.size()-windowSize+1);

        NdArray<dtype> weightsFlat = fliplr(inWeights.flatten());

        const uint32 endPointRow = output.size();

        for (uint32 i = 0; i < endPointRow; ++i)
        {
            NdArray<dtype> window = arrayWithBoundary[Slice(i, i+windowSize)].flatten();

            output[i] = dot(window, weightsFlat).item();
        }

        return output;
    }
} // namespace nc::filter
