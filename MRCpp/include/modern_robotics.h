#pragma once

#include <Eigen/Dense>
#include <vector>

namespace mr {

/*
 * Function: Find if the value is negligible enough to consider 0
 * Inputs: value to be checked as a double
 * Returns: Boolean of true-ignore or false-can't ignore
 */
bool NearZero(const double);

/*
 * Function: Calculate the 6x6 matrix [adV] of the given 6-vector
 * Input: Eigen::VectorXd (6x1)
 * Output: Eigen::MatrixXd (6x6)
 * Note: Can be used to calculate the Lie bracket [V1, V2] = [adV1]V2
 */
Eigen::MatrixXd ad(Eigen::VectorXd);


/*
 * Function: Returns a normalized version of the input vector
 * Input: Eigen::MatrixXd
 * Output: Eigen::MatrixXd
 * Note: MatrixXd is used instead of VectorXd for the case of row vectors
 * 		Requires a copy
 *		Useful because of the MatrixXd casting
 */
Eigen::MatrixXd Normalize(Eigen::MatrixXd);


/*
 * Function: Returns the skew symmetric matrix representation of an angular velocity vector
 * Input: Eigen::Vector3d 3x1 angular velocity vector
 * Returns: Eigen::MatrixXd 3x3 skew symmetric matrix
 */
Eigen::Matrix3d VecToso3(const Eigen::Vector3d&);


/*
 * Function: Returns angular velocity vector represented by the skew symmetric matrix
 * Inputs: Eigen::MatrixXd 3x3 skew symmetric matrix
 * Returns: Eigen::Vector3d 3x1 angular velocity
 */
Eigen::Vector3d so3ToVec(const Eigen::MatrixXd&);


/*
 * Function: Tranlates an exponential rotation into it's individual components
 * Inputs: Exponential rotation (rotation matrix in terms of a rotation axis
 *				and the angle of rotation)
 * Returns: The axis and angle of rotation as [x, y, z, theta]
 */
Eigen::Vector4d AxisAng3(const Eigen::Vector3d&);


/*
 * Function: Translates an exponential rotation into a rotation matrix
 * Inputs: exponenential representation of a rotation
 * Returns: Rotation matrix
 */
Eigen::Matrix3d MatrixExp3(const Eigen::Matrix3d&);


/* Function: Computes the matrix logarithm of a rotation matrix
 * Inputs: Rotation matrix
 * Returns: matrix logarithm of a rotation
 */
Eigen::Matrix3d MatrixLog3(const Eigen::Matrix3d&);


/*
 * Function: Combines a rotation matrix and position vector into a single
 * 				Special Euclidian Group (SE3) homogeneous transformation matrix
 * Inputs: Rotation Matrix (R), Position Vector (p)
 * Returns: Matrix of T = [ [R, p],
 *						    [0, 1] ]
 */
Eigen::MatrixXd RpToTrans(const Eigen::Matrix3d&, const Eigen::Vector3d&);


/*
 * Function: Separates the rotation matrix and position vector from
 *				the transfomation matrix representation
 * Inputs: Homogeneous transformation matrix
 * Returns: std::vector of [rotation matrix, position vector]
 */
std::vector<Eigen::MatrixXd> TransToRp(const Eigen::MatrixXd&);


/*
 * Function: Translates a spatial velocity vector into a transformation matrix
 * Inputs: Spatial velocity vector [angular velocity, linear velocity]
 * Returns: Transformation matrix
 */
Eigen::MatrixXd VecTose3(const Eigen::VectorXd&);


/* Function: Translates a transformation matrix into a spatial velocity vector
 * Inputs: Transformation matrix
 * Returns: Spatial velocity vector [angular velocity, linear velocity]
 */
Eigen::VectorXd se3ToVec(const Eigen::MatrixXd&);


/*
 * Function: Provides the adjoint representation of a transformation matrix
 *			 Used to change the frame of reference for spatial velocity vectors
 * Inputs: 4x4 Transformation matrix SE(3)
 * Returns: 6x6 Adjoint Representation of the matrix
 */
Eigen::MatrixXd Adjoint(const Eigen::MatrixXd&);


/*
 * Function: Rotation expanded for screw axis
 * Inputs: se3 matrix representation of exponential coordinates (transformation matrix)
 * Returns: 6x6 Matrix representing the rotation
 */
Eigen::MatrixXd MatrixExp6(const Eigen::MatrixXd&);


/*
 * Function: Computes the matrix logarithm of a homogeneous transformation matrix
 * Inputs: R: Transformation matrix in SE3
 * Returns: The matrix logarithm of R
 */
Eigen::MatrixXd MatrixLog6(const Eigen::MatrixXd&);


/*
 * Function: Compute end effector frame (used for current spatial position calculation)
 * Inputs: Home configuration (position and orientation) of end-effector
 *		   The joint screw axes in the space frame when the manipulator
 *             is at the home position
 * 		   A list of joint coordinates.
 * Returns: Transfomation matrix representing the end-effector frame when the joints are
 *				at the specified coordinates
 * Notes: FK means Forward Kinematics
 */
Eigen::MatrixXd FKinSpace(const Eigen::MatrixXd&, const Eigen::MatrixXd&, const Eigen::VectorXd&);

/*
 * Function: Compute end effector frame (used for current body position calculation)
 * Inputs: Home configuration (position and orientation) of end-effector
 *		   The joint screw axes in the body frame when the manipulator
 *             is at the home position
 * 		   A list of joint coordinates.
 * Returns: Transfomation matrix representing the end-effector frame when the joints are
 *				at the specified coordinates
 * Notes: FK means Forward Kinematics
 */
Eigen::MatrixXd FKinBody(const Eigen::MatrixXd&, const Eigen::MatrixXd&, const Eigen::VectorXd&);


/*
 * Function: Gives the space Jacobian
 * Inputs: Screw axis in home position, joint configuration
 * Returns: 6xn Spatial Jacobian
 */
Eigen::MatrixXd JacobianSpace(const Eigen::MatrixXd&, const Eigen::MatrixXd&);


/*
 * Function: Gives the body Jacobian
 * Inputs: Screw axis in BODY position, joint configuration
 * Returns: 6xn Bobdy Jacobian
 */
Eigen::MatrixXd JacobianBody(const Eigen::MatrixXd&, const Eigen::MatrixXd&);


/*
 * Inverts a homogeneous transformation matrix
 * Inputs: A homogeneous transformation Matrix T
 * Returns: The inverse of T
 */
Eigen::MatrixXd TransInv(const Eigen::MatrixXd&);

/*
 * Inverts a rotation matrix
 * Inputs: A rotation matrix  R
 * Returns: The inverse of R
 */
Eigen::MatrixXd RotInv(const Eigen::MatrixXd&);

/*
 * Takes a parametric description of a screw axis and converts it to a
 * normalized screw axis
 * Inputs:
 * q: A point lying on the screw axis
 * s: A unit vector in the direction of the screw axis
 * h: The pitch of the screw axis
 * Returns: A normalized screw axis described by the inputs
 */
Eigen::VectorXd ScrewToAxis(Eigen::Vector3d q, Eigen::Vector3d s, double h);


/*
 * Function: Translates a 6-vector of exponential coordinates into screw
 * axis-angle form
 * Inputs: 
 * expc6: A 6-vector of exponential coordinates for rigid-body motion
          S*theta
 * Returns: The corresponding normalized screw axis S; The distance theta traveled
 * along/about S in form [S, theta]
 * Note: Is it better to return std::map<S, theta>?
 */
Eigen::VectorXd AxisAng6(const Eigen::VectorXd&);


/*
 * Function: Returns projection of one matrix into SO(3)
 * Inputs:
 * M:		A matrix near SO(3) to project to SO(3)
 * Returns: The closest matrix R that is in SO(3)
 * Projects a matrix mat to the closest matrix in SO(3) using singular-value decomposition
 * (see http://hades.mech.northwestern.edu/index.php/Modern_Robotics_Linear_Algebra_Review).
 * This function is only appropriate for matrices close to SO(3).
 */
Eigen::MatrixXd ProjectToSO3(const Eigen::MatrixXd&);


/*
 * Function: Returns projection of one matrix into SE(3)
 * Inputs:
 * M:		A 4x4 matrix near SE(3) to project to SE(3)
 * Returns: The closest matrix T that is in SE(3)
 * Projects a matrix mat to the closest matrix in SO(3) using singular-value decomposition
 * (see http://hades.mech.northwestern.edu/index.php/Modern_Robotics_Linear_Algebra_Review).
 * This function is only appropriate for matrices close to SE(3).
 */
Eigen::MatrixXd ProjectToSE3(const Eigen::MatrixXd&);


/*
 * Function: Returns the Frobenius norm to describe the distance of M from the SO(3) manifold
 * Inputs:
 * M: A 3x3 matrix
 * Outputs:
 *	 the distance from mat to the SO(3) manifold using the following
 * method:
 *  If det(M) <= 0, return a large number.
 *  If det(M) > 0, return norm(M^T*M - I).
 */
double DistanceToSO3(const Eigen::Matrix3d&);


/*
 * Function: Returns the Frobenius norm to describe the distance of mat from the SE(3) manifold
 * Inputs:
 * T: A 4x4 matrix
 * Outputs:
 *	 the distance from T to the SE(3) manifold using the following
 * method:
 *  Compute the determinant of matR, the top 3x3 submatrix of T.
 *  If det(matR) <= 0, return a large number.
 *  If det(matR) > 0, replace the top 3x3 submatrix of mat with matR^T*matR,
 *  and set the first three entries of the fourth column of mat to zero. Then
 *  return norm(T - I).
 */
double DistanceToSE3(const Eigen::Matrix4d&);


/*
 * Function: Returns true if M is close to or on the manifold SO(3)
 * Inputs:
 * M: A 3x3 matrix
 * Outputs:
 *	 true if M is very close to or in SO(3), false otherwise
 */
bool TestIfSO3(const Eigen::Matrix3d&);


/*
 * Function: Returns true if T is close to or on the manifold SE(3)
 * Inputs:
 * M: A 4x4 matrix
 * Outputs:
 *	 true if T is very close to or in SE(3), false otherwise
 */
bool TestIfSE3(const Eigen::Matrix4d&);


/*
 * Function: Computes inverse kinematics in the body frame for an open chain robot
 * Inputs:
 *	Blist: The joint screw axes in the end-effector frame when the
 *         manipulator is at the home position, in the format of a
 *         matrix with axes as the columns
 *	M: The home configuration of the end-effector
 *	T: The desired end-effector configuration Tsd
 *	thetalist[in][out]: An initial guess and result output of joint angles that are close to
 *         satisfying Tsd
 *	emog: A small positive tolerance on the end-effector orientation
 *        error. The returned joint angles must give an end-effector
 *        orientation error less than eomg
 *	ev: A small positive tolerance on the end-effector linear position
 *      error. The returned joint angles must give an end-effector
 *      position error less than ev
 * Outputs:
 *	success: A logical value where TRUE means that the function found
 *           a solution and FALSE means that it ran through the set
 *           number of maximum iterations without finding a solution
 *           within the tolerances eomg and ev.
 *	thetalist[in][out]: Joint angles that achieve T within the specified tolerances,
 */
bool IKinBody(const Eigen::MatrixXd&, const Eigen::MatrixXd&, const Eigen::MatrixXd&, Eigen::VectorXd&, double, double);


/*
 * Function: Computes inverse kinematics in the space frame for an open chain robot
 * Inputs:
 *	Slist: The joint screw axes in the space frame when the
 *         manipulator is at the home position, in the format of a
 *         matrix with axes as the columns
 *	M: The home configuration of the end-effector
 *	T: The desired end-effector configuration Tsd
 *	thetalist[in][out]: An initial guess and result output of joint angles that are close to
 *         satisfying Tsd
 *	emog: A small positive tolerance on the end-effector orientation
 *        error. The returned joint angles must give an end-effector
 *        orientation error less than eomg
 *	ev: A small positive tolerance on the end-effector linear position
 *      error. The returned joint angles must give an end-effector
 *      position error less than ev
 * Outputs:
 *	success: A logical value where TRUE means that the function found
 *           a solution and FALSE means that it ran through the set
 *           number of maximum iterations without finding a solution
 *           within the tolerances eomg and ev.
 *	thetalist[in][out]: Joint angles that achieve T within the specified tolerances,
 */
bool IKinSpace(const Eigen::MatrixXd&, const Eigen::MatrixXd&, const Eigen::MatrixXd&, Eigen::VectorXd&, double, double);


/*
 * Function: Computes inverse dynamics in the space frame for an open chain robot
 * Inputs:
 *	thetalist: n-vector of joint variables
 *	dthetalist: n-vector of joint rates
 *	ddthetalist: n-vector of joint accelerations
 *	g: Gravity vector g
 *	Ftip: Spatial force applied by the end-effector expressed in frame {n+1}
 *  Mlist: List of link frames i relative to i-1 at the home position
 *	Glist: Spatial inertia matrices Gi of the links
 *	Slist: Screw axes Si of the joints in a space frame, in the format
 *         of a matrix with axes as the columns
 * Outputs:
 *	taulist: The n-vector of required joint forces/torques
 * Notes:
 *   This function uses forward-backward Newton-Euler iterations to solve the equation:
 *   taulist = Mlist(thetalist)ddthetalist + c(thetalist,dthetalist) \
 *             + g(thetalist) + Jtr(thetalist)Ftip
 */
Eigen::VectorXd InverseDynamics(const Eigen::VectorXd&, const Eigen::VectorXd&, const Eigen::VectorXd&, const Eigen::VectorXd&,
	const Eigen::VectorXd&, const std::vector<Eigen::MatrixXd>&, const std::vector<Eigen::MatrixXd>&, const Eigen::MatrixXd&);


/*
 * Function: Computes the mass matrix of an open chain robot based on the given configuration
 * Inputs:
 *	thetalist: A list of joint variables
 *  Mlist: List of link frames i relative to i-1 at the home position
 *	Glist: Spatial inertia matrices Gi of the links
 *	Slist: Screw axes Si of the joints in a space frame, in the format
 *         of a matrix with axes as the columns
 * Outputs:
 *	M: The numerical inertia matrix M(thetalist) of an n-joint serial
 *     chain at the given configuration thetalist
 * Notes:
 *	This function calls InverseDynamics n times, each time passing a
 *  ddthetalist vector with a single element equal to one and all other
 *  inputs set to zero.
 *  Each call of InverseDynamics generates a single column, and these columns
 *  are assembled to create the inertia matrix.
 */
Eigen::MatrixXd MassMatrix(const Eigen::VectorXd&, const std::vector<Eigen::MatrixXd>&, const std::vector<Eigen::MatrixXd>&, const Eigen::MatrixXd&);


/*
 * Function: Computes the Coriolis and centripetal terms in the inverse dynamics of an open chain robot
 * Inputs:
 *	thetalist: A list of joint variables
 *	dthetalist: A list of joint rates
 *  Mlist: List of link frames i relative to i-1 at the home position
 *	Glist: Spatial inertia matrices Gi of the links
 *	Slist: Screw axes Si of the joints in a space frame, in the format
 *         of a matrix with axes as the columns
 * Outputs:
 *	vqForces: The vector c(thetalist,dthetalist) of Coriolis and centripetal
 *			  terms for a given thetalist and dthetalist
 * Notes:
 *	This function calls InverseDynamics with g = 0, Ftip = 0, and
*   ddthetalist = 0.
 */
Eigen::VectorXd VelQuadraticForces(const Eigen::VectorXd&, const Eigen::VectorXd&, const std::vector<Eigen::MatrixXd>&,
	const std::vector<Eigen::MatrixXd>&, const Eigen::MatrixXd&);
}