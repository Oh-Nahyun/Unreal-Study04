#pragma once

#include "framework.h"

//Begin vector_3d----------------------------------------------------

typedef FLOAT scalar;

class vector_3d
{
public:
    scalar x,y,z;

public:
    vector_3d(void);
    vector_3d(
        scalar xComponent,
        scalar yComponent,
        scalar zComponent);
    vector_3d(
        const vector_3d &rightOperand);

    void X(
        scalar xComponent);
    scalar X(void);

    void Y(
        scalar yComponent);
    scalar Y(void);

    void Z(
        scalar yComponent);
    scalar Z(void);

    void SetXYZ(
        scalar xComponent,
        scalar yComponent,
        scalar zComponent);
    void GetXYZ(
        scalar &xComponent,
        scalar &yComponent,
        scalar &zComponent);

    vector_3d &operator =(
        const vector_3d &rightOperand);

    vector_3d operator +(
        const vector_3d &rightOperand);
    vector_3d operator +=(
        const vector_3d &rightOperand);
    vector_3d operator -(
        const vector_3d &rightOperand);
    vector_3d operator -=(
        const vector_3d &rightOperand);
    vector_3d operator *(
        scalar rightOperand);
    friend vector_3d operator *(
        scalar leftOperand,
        const vector_3d &rightOperand);

    vector_3d operator *=(
        scalar rightOperand);
    vector_3d operator /(
        scalar rightOperand);
    vector_3d operator /=(
        scalar rightOperand);

    scalar Dot(
        const vector_3d &v1);
    scalar Norm(void);
    scalar NormSquared(void);

    vector_3d Cross(
        const vector_3d &rightOperand);
    vector_3d Normalize(
        scalar tolerance);

    operator vector_3d();
};

//Begin Inline Functions for the vector_3d Class---------------------

/*
Function:   vector_3d
Member of:  vector_3d
Parameters
    Input:  None.
    Output: None.
Returns:    Nothing.
Comments:   No-arg constructor.
*/
inline vector_3d::vector_3d(void)
{
    x=y=z=0;
}


/*
Function:   vector_3d
Member of:  vector_3d
Parameters
    Input:  xComponent - Contains the value for the new vector's x component.
            yComponent - Contains the value for the new vector's y component.
            zComponent - Contains the value for the new vector's z component.
    Output: None.
Returns:    Nothing.
Comments:   No-arg constructor.
*/
inline vector_3d::vector_3d(
    scalar xComponent,
    scalar yComponent,
    scalar zComponent)
{
    x=xComponent;
    y=yComponent;
    z=zComponent;
}


/*
Function:   vector_3d
Member of:  vector_3d
Parameters
    Input:  sourceVector - Contains the from which the new vector will be initialized.
    Output: None.
Returns:    Nothing.
Comments:   Copy constructor. Used to initialize a vector from a vector.
*/
inline vector_3d::vector_3d(
    const vector_3d &sourceVector)
{
    x=sourceVector.x;
    y=sourceVector.y;
    z=sourceVector.z;
}


/*
Function:   X
Member of:  vector_3d
Parameters
    Input:  xComponent - Contains the value for the new vector's x component.
    Output: None.
Returns:    Nothing.
Comments:   Use this function to set the vector's x component.
*/
inline void vector_3d::X(
    scalar xComponent)
{
    x=xComponent;
}


/*
Function:   X
Member of:  vector_3d
Parameters
    Input:  None.
    Output: None.
Returns:    Returns the magnitude of the vector's x component.
Comments:   Use this function to get the vector's x component.
*/
inline scalar vector_3d::X(void)
{
    return(x);
}


/*
Function:   Y
Member of:  vector_3d
Parameters
    Input:  yComponent - Contains the value for the new vector's y component.
    Output: None.
Returns:    Nothing.
Comments:   Use this function to set the vector's y component.
*/
inline void vector_3d::Y(
    scalar yComponent)
{
    y=yComponent;
}


/*
Function:   Y
Member of:  vector_3d
Parameters
    Input:  None.
    Output: None.
Returns:    Returns the magnitude of the vector's y component.
Comments:   Use this function to get the vector's y component.
*/
inline scalar vector_3d::Y(void)
{
    return(y);
}


/*
Function:   Z
Member of:  vector_3d
Parameters
    Input:  yComponent - Contains the value for the new vector's z component.
    Output: None.
Returns:    Nothing.
Comments:   Use this function to set the vector's z component.
*/
inline void vector_3d::Z(
    scalar zComponent)
{
    z=zComponent;
}


/*
Function:   Z
Member of:  vector_3d
Parameters
    Input:  None.
    Output: None.
Returns:    Returns the magnitude of the vector's z component.
Comments:   Use this function to get the vector's z component.
*/
inline scalar vector_3d::Z(void)
{
    return(z);
}


/*
Function:   SetXYZ
Member of:  vector_3d
Parameters
    Input:  xComponent - Contains the value for the vector's x component.
            yComponent - Contains the value for the vector's y component.
            zComponent - Contains the value for the vector's z component.
    Output: None.
Returns:    Nothing.
Comments:   Use this function to set the vector's x, y, and z components.
*/
inline void vector_3d::SetXYZ(
    scalar xComponent,
    scalar yComponent,
    scalar zComponent)
{
    x=xComponent;
    y=yComponent;
    z=zComponent;
}


/*
Function:   GetXYZ
Member of:  vector_3d
Parameters
    Input:  None.
    Output: xComponent - Contains the value for the vector's x component.
            yComponent - Contains the value for the vector's y component.
            yComponent - Contains the value for the vector's z component.
Returns:    Nothing.
Comments:   Use this function to get the vector's x and y components.
*/
inline void vector_3d::GetXYZ(
    scalar &xComponent,
    scalar &yComponent,
    scalar &zComponent)
{
    xComponent=x;
    yComponent=y;
    zComponent=z;
}


/*
Function:   operator =
Member of:  vector_3d
Parameters
    Input:  rightOperand - Contains the vector whose values will be assigned.
    Output: None.
Returns:    Returns the value assigned.
Comments:   Assigns a vector to a vector.
*/
inline vector_3d &vector_3d::operator =(
    const vector_3d &rightOperand)
{
    x=rightOperand.x;
    y=rightOperand.y;
    z=rightOperand.z;

    return (*this);
}


/*
Function:   operator +
Member of:  vector_3d
Parameters
    Input:  rightOperand - Contains the right-hand operand of the addition.
    Output: None.
Returns:    Returns a vector containing the result of the addition.
Comments:   Adds two vectors.
*/
inline vector_3d vector_3d::operator +(
    const vector_3d &rightOperand)
{
    return(vector_3d(x+rightOperand.x,y+rightOperand.y,z+rightOperand.z));
}


/*
Function:   operator +=
Member of:  vector_3d
Parameters
    Input:  rightOperand - Contains the right-hand operand of the addition.
    Output: None.
Returns:    Returns a vector containing the result of the addition.
Comments:   Adds two vectors.
*/
inline vector_3d vector_3d::operator +=(
    const vector_3d &rightOperand)
{
    x+=rightOperand.x;
    y+=rightOperand.y;
    z+=rightOperand.z;
    return(*this);
}


/*
Function:   operator -
Member of:  vector_3d
Parameters
    Input:  rightOperand - Contains the right-hand operand of the subtraction.
    Output: None.
Returns:    Returns a vector containing the result of the subtraction.
Comments:   Subtracts two vectors.
*/
inline vector_3d vector_3d::operator -(
    const vector_3d &rightOperand)
{
    return(vector_3d(x-rightOperand.x,y-rightOperand.y,z-rightOperand.z));
}


/*
Function:   operator -=
Member of:  vector_3d
Parameters
    Input:  rightOperand - Contains the right-hand operand of the subtraction.
    Output: None.
Returns:    Returns a vector containing the result of the subtraction.
Comments:   Subtracts two vectors.
*/
inline vector_3d vector_3d::operator -=(
    const vector_3d &rightOperand)
{
    x-=rightOperand.x;
    y-=rightOperand.y;
    z-=rightOperand.z;
    return(*this);
}



/*
Function:   operator *
Member of:  vector_3d
Parameters
    Input:  rightOperand - Contains the right-hand operand of the multiplication.
    Output: None.
Returns:    Returns a vector containing the result of the multiplcation.
Comments:   Multiplies vector by a scalar.
*/
inline vector_3d vector_3d::operator *(
    scalar rightOperand)
{
    return(vector_3d(x*rightOperand,y*rightOperand,z*rightOperand));
}
 

/*
Function:   operator *
Member of:  vector_3d
Parameters
    Input:  leftOperand - Contains the left-hand operand of the multiplication.
            rightOperand - Contains the right-hand operand of the multiplication.
    Output: None.
Returns:    Returns a vector containing the result of the multiplcation.
Comments:   Multiplies scalar by a vector.
*/
inline vector_3d operator *(
    scalar leftOperand,
    const vector_3d &rightOperand)
{
    return(vector_3d(leftOperand*rightOperand.x,
                     leftOperand*rightOperand.y,
                     leftOperand*rightOperand.z));
}


/*
Function:   operator *=
Member of:  vector_3d
Parameters
    Input:  rightOperand - Contains the right-hand operand of the multiplication.
    Output: None.
Returns:    Returns a vector containing the result of the multiplcation.
Comments:   Multiplies scalar by a vector.
*/
inline vector_3d vector_3d::operator *=(
    scalar rightOperand)
{
    x*=rightOperand;
    y*=rightOperand;
    z*=rightOperand;
    return(*this);
}


/*
Function:   operator /
Member of:  vector_3d
Parameters
    Input:  rightOperand - Contains the right-hand operand of the multiplication.
    Output: None.
Returns:    Returns a vector containing the result of the division.
Comments:   Divides a vector by a scalar.
*/
inline vector_3d vector_3d::operator /(
    scalar rightOperand)
{
    return(vector_3d(x/rightOperand,y/rightOperand,z/rightOperand));
}


/*
Function:   operator /=
Member of:  vector_3d
Parameters
    Input:  rightOperand - Contains the right-hand operand of the multiplication.
    Output: None.
Returns:    Returns a vector containing the result of the division.
Comments:   Divides a vector by a scalar.
*/
inline vector_3d vector_3d::operator /=(
    scalar rightOperand)
{
    x/=rightOperand;
    y/=rightOperand;
    z/=rightOperand;
    return(*this);
}


/*
Function:   Dot
Member of:  vector_2d
Parameters
    Input:  v1 - Contains the vector to be dotted with the current 
                vector.
    Output: None.
Returns:    Returns a scalar containing the dot product.
Comments:   Calculates the dot product of two vectors.
*/
inline scalar vector_3d::Dot(
    const vector_3d &v1)
{
    return(x*v1.x + y*v1.y + z*v1.z);
}


/*
Function:   Norm
Member of:  vector_3d
Parameters
    Input:  None.
    Output: None.
Returns:    Returns a scalar containing the norm of a vector.
Comments:   Calculates the norm, or magnitude of a vector.
*/
inline scalar vector_3d::Norm(void)
{
    return(sqrtf(x*x + y*y + z*z));
}


/*
Function:   NormSquared
Member of:  vector_3d
Parameters
    Input:  None.
    Output: None.
Returns:    Returns the length of a vector squared.
Comments:   Calculates the length of a vector squared.
*/
inline scalar vector_3d::NormSquared(void)
{
    return(x*x + y*y + z*z);
}


/*
Function:   Cross
Member of:  vector_3d
Parameters
    Input:  None.
    Output: None.
Returns:    Returns a vector containing the cross product of the two vectors.
Comments:   Calculates the dot product of the two input vectors.
*/
inline vector_3d vector_3d::Cross(
    const vector_3d &rightOperand)
{
    return(
        vector_3d(
            y*rightOperand.z - z*rightOperand.y,
            z*rightOperand.x - x*rightOperand.z,
            x*rightOperand.y - y*rightOperand.x));
}


/*
Function:   Normalize
Member of:  vector_3d
Parameters
    Input:  None.
    Output: None.
Returns:    Returns the normal of a vector.
Comments:   Calculates a vector that points in the same direction as 
            the current vector, but has a length of 1.
*/
inline vector_3d vector_3d::Normalize(
    scalar tolerance)
{
    vector_3d result;

    scalar length = Norm();
    if (length>=tolerance)
    {
        result.x = x/length;
        result.y = y/length;
        result.z = z/length;
    }
    return(result);
}

//End Inline Functions for the vector_3d Class-----------------------


//End vector_3d------------------------------------------------------
