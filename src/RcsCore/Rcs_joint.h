/*******************************************************************************

  Copyright (c) 2017, Honda Research Institute Europe GmbH.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. All advertising materials mentioning features or use of this software
     must display the following acknowledgement: This product includes
     software developed by the Honda Research Institute Europe GmbH.

  4. Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

#ifndef RCS_JOINT_H
#define RCS_JOINT_H


#include "Rcs_graph.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \defgroup RcsJointFunctions Joints
 */


/*! \ingroup RcsJointFunctions
 *  \brief Destroys the joint and frees all memory. If self is already NULL,
 *         the function does nothing.
 */
void RcsJoint_destroy(RcsJoint* self);

/*! \ingroup RcsJointFunctions
 *  \brief Makes a deep copy of a RcsJoint data structure. Some pointers
 *         can't be assigned in this context. This are
 *         <br>
 *         - RcsJoint *prev
 *         - RcsJoint *next
 *         - RcsJoint *coupledJoint
 *         - void* extraInfo
 *         <br>
 *         These are left unchanged and need to be handled separately.
 */
void RcsJoint_copy(RcsJoint* dst, const RcsJoint* src);

/*! \ingroup RcsJointFunctions
 *  \brief Prints the joint data to a file descriptor.
 */
void RcsJoint_fprint(FILE* out, const RcsJoint* self);

/*! \ingroup RcsJointFunctions
 *  \brief Returns true if the joint is a rotational joint, false otherwise.
 *         The function also returns false if joint is NULL.
 */
bool RcsJoint_isRotation(const RcsJoint* joint);

/*! \ingroup RcsJointFunctions
 *  \brief Returns true if the joint is a translational joint, false
 *         otherwise. The function also returns false if joint is NULL.
 */
bool RcsJoint_isTranslation(const RcsJoint* joint);

/*! \ingroup RcsJointFunctions
 *  \brief Prints the type of the joint to a file descriptor.
 */
void RcsJoint_fprintType(FILE* out, const RcsJoint* jnt);

/*! \ingroup RcsJointFunctions
 *  \brief Returns a character string holding the enumeration type name of
 *         the joint type. If the type is not known, "Unknown joint type"
 *         will be returned.
 */
const char* RcsJoint_typeName(int type);

/*! \ingroup RcsJointFunctions
 *  \brief Return joint angle of salve joint with respect to master joint
 *         angle. This function computes a polynomial in the form <br>
 *         q_sl = p0*q_m^4 + p1*q_m^3 + p2*q_m^2 + p3*q_m + p4
 */
/* double RcsJoint_calcSlaveJointAngle(const double q_master, */
/*                                     const double depend_coef[4]); */

/*! \ingroup RcsJointFunctions
 *  \brief Return sensitivity of salve joint with respect to master joint.
 */
/* double RcsJoint_calcSlaveJointSensitive(const double q_master, */
/*                                         const double depend_coef[4]); */

/*! \ingroup RcsJointFunctions
 *  \brief Returns the joint position of the salve joint with respect to
 *         master joint position.
 *
 *         This function returns the slave joint position given the joint
 *         position of the master joint (q_master), and the master joint
 *         data structure.
 *         <br><br>
 *         If the coefficients are of polynomial degree 5,
 *         the function RcsJoint_calcSlaveJointAngle() is used. If in this
 *         case the joint limit of the master joint is violated, the slave
 *         joint angle is computed as the joint limit, which is linearly
 *         interpolated into the limit using the joint sensitivity at the
 *         limit. This allows to extend the joint range into the invalid
 *         region, which is sometimes needed for simulation, planning and
 *         optimization.
 *         <br><br>
 *         If the coefficients are of polynomial degree 1, a linear
 *         interpolation with the coupling factor is done.
 *         <br><br>
 *         If the coefficients are of polynomial degree other than 1 or 5,
 *         the function exits with a fatal error.
 */
double RcsJoint_computeSlaveJointAngle(const RcsJoint* slave,
                                       const double q_master);

/*! \ingroup RcsJointFunctions
 *  \brief Return joint velocity of salve joint with respect to master joint
 *         velocity. This function works in the samee way as
 *         RcsJoint_computeSlaveJointAngle().
 */
double RcsJoint_computeSlaveJointVelocity(const RcsJoint* slave,
                                          const double q_master,
                                          const double qp_master);

/*! \ingroup RcsJointFunctions
 *  \brief Prints the joint's xml representation to the given file
 *         descriptor. Both arguments are assumed to be not NULL. Otherwise,
 *         the function exits with a fatal error.
 */
void RcsJoint_fprintXML(FILE* out, const RcsJoint* self);

/*! \ingroup RcsJointFunctions
 *  \brief Returns the joint's index in an array of RcsGraph::dof elements. If
 *         self is NULL, -1 is returned.
 */
int RcsJoint_getJointIndex(const RcsJoint* self);

/*! \ingroup RcsJointFunctions
*  \brief Returns the joint's directionel index:
*         - 0 for RCSJOINT_ROT_X and RCSJOINT_TRANS_X
*         - 1 for RCSJOINT_ROT_Y and RCSJOINT_TRANS_Y
*         - 2 for RCSJOINT_ROT_Z and RCSJOINT_TRANS_Z
*
*         If the joint type doesn't match any of these, the function returns -1.
*/
int RcsJoint_getDirectionIndex(const RcsJoint* self);

/*! \ingroup RcsJointFunctions
 *  \brief Scales the geometry of the joint.
 *
 *  \param[in,out] joint    Joint to be reshaped.
 *  \param[in] scale        Scaling factor.
 */
void RcsJoint_scale(RcsJoint* joint, double scale);


#ifdef __cplusplus
}
#endif

#endif   // RCS_JOINT_H
