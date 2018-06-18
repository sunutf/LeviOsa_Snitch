#include <math.h>

// DR: Can I use malloc or any heap allocation functions?
void matrixInverse(float m[3][3], float (*minv)[3][3]) {
	float det = m[0][0]* (m[1][1]* m[2][2]- m[2][1]* m[1][2])-
	             m[0][1]* (m[1][0]* m[2][2]- m[1][2]* m[2][0])+
	             m[0][2]* (m[1][0]* m[2][1]- m[1][1]* m[2][0]);
	float invdet = 1 / det;

	(*minv)[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invdet;
	(*minv)[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invdet;
	(*minv)[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;
	(*minv)[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invdet;
	(*minv)[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invdet;
	(*minv)[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * invdet;
	(*minv)[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invdet;
	(*minv)[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * invdet;
	(*minv)[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet;
}

void matrixMul(float mat[3][3], float vec[3], float (*res)[3]) {
	for (int i = 0; i < 3; i++) {
		(*res)[i] = 0;
		for (int j = 0; j < 3; j++) {
			(*res)[i] += mat[i][j] * vec[j];
		}
	}
}

float norm(float vec[3]) {
	return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
}

float innerProduct(float vec1[3], float vec2[3]) {
	return vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2];
}
