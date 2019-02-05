#include "vector3.h"
#include <iostream>
#include <vector>

/* Fills a vector with orthogonal base vectors by using Gram-Schmidt orthogonalization method*/
void OrthoGramSchmidt(const std::vector<Vector3> &in, std::vector<Vector3> &out);
void TestVector();
void PrintBaseVectors(const std::vector<Vector3> &base);

int main(int argc, char **argv)
{
	std::vector<Vector3> linealIndependent = {
		Vector3(0.0f, 1.0f, 1.0f), 
		Vector3(1.0f, 0.0f, 0.0f), 
		Vector3(0.0f, 1.0, 0.0f)};

	std::vector<Vector3> orthogonalBase;

	OrthoGramSchmidt(linealIndependent, orthogonalBase);

	PrintBaseVectors(linealIndependent);
	PrintBaseVectors(orthogonalBase);


	getchar();
	
	return 0;
}
/* generates 3 orthogonal vectors out of 3 base vectors (the resulting vectors are not normalized)*/
void OrthoGramSchmidt(const std::vector<Vector3> &in, std::vector<Vector3> &out)
{
	out.push_back(in[0]);
	for (int i = 1; i < 3; ++i)
	{
		Vector3 projected;
		for (int k = 0; k <= i - 1; ++k)
		{
			projected += ProjectOn(in[i], out[k]);
		}

		out.push_back(in[i] - projected);
	}
}

void TestVector() {
	Vector3 v1(1.0f, 1.0f, 1.0f);

	Vector3 copy;
	copy = v1;
	std::cout << "copia de v1: copy = " << copy << std::endl;

	copy += copy;
	std::cout << "suma asignación de copy: " << copy << std::endl;

	copy = copy - copy;
	std::cout << "resta de copy-copy: " << copy << std::endl;

	v1 = 2.0f * v1;
	std::cout << "2.0f * v1: " << v1 << std::endl;

	v1 = v1 * 2.0f;
	std::cout << "2.0f * v1: " << v1 << std::endl;
}

void PrintBaseVectors(const std::vector<Vector3> &base)
{
	std::cout << "Base: ";
	for (const Vector3 &v : base)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
}