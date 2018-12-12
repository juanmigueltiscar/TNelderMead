// ============================================================================= TNELDERMEAD.H
//
// Clase TNELDERMEAD
//
// Clase Template que aplica el algoritmo Nelder-Mead con restricción.
// Funciona para cualquier función con infinitos valores de x-->{x[0],x[1],x[2]...}
//
//
// Adaptació a C++  de la implementació de
// Michael F. Hutt 1997 del métode simplex Nelder-Mead.
//
// =================================================================== 03/12/2018

// =================================================================== EJEMPLO DE FUNCIONAMIENTO
//
// Función objetivo: y = 50x^4 - 5x^2 + x - 1
// Restricción:      x < 30 (introducida como una penalización)
// Valor inicial: x = 5
//
// std::vector<REAL_> start(1); start[0] = 5.0; //Valor inicial tentativo
// auto Fn = [&](std::vector<REAL_> &x) ->REAL_ {return 50.0*x[0] * x[0] * x[0] * x[0] - 5.0*x[0] * x[0] + x[0] - 1; }; //Función objetivo
// auto constr = [&](std::vector<REAL_> &x) ->void {if (fabs(x[0]) > 30) x[0] = x[0] - 50000.0; }; //Función de penalización
// 
// TNelderMead Optim(start, 1E-8, 1); //Inicialización
// REAL_ a = Optim.MinSearch(Fn, constr, true); //Optimización (devuelve el valor mínimo de la función objetivo)
// REAL_ b = Optim.xvalues()[0]; //Devuelve el valor de x que da el valor mínimo de la función
//
// ================================================================================== INCLUDES
#ifndef TNELDERMEAD_H
#define TNELDERMEAD_H

#include "gbl.h"
#include <vector>
#include <functional>

constexpr uint32_t MAX_IT   =   1000;      /* maximum number of iterations */
constexpr REAL_     ALPHA   =    1.0;       /* reflection coefficient */
constexpr REAL_      BETA   =    0.5;       /* contraction coefficient */
constexpr REAL_     GAMMA   =    2.0;       /* expansion coefficient */


using TPtrPtr = std::vector<std::vector<REAL_>>;
using PrintIterations = bool;

template<size_t n=1>
class TNelderMead
{
private:

	std::vector<REAL_> start{n};

	REAL_                eps,
		               scale;

	TPtrPtr                v;


public:
	TNelderMead() = delete;
	TNelderMead(const std::vector<REAL_> &start_, REAL_ eps_, REAL_ scale_) noexcept :
		         start(start_), eps(eps_), scale(scale_)  {}

	void initialize_simplex();
	void print_initial_simplex(const std::vector<REAL_> &f) const;
	void print_iteration(const std::vector<REAL_> &f, int itr) const;

	size_t vg_index(std::vector<REAL_> &f, size_t vg);
	size_t vs_index(std::vector<REAL_> &f, size_t vs);
	size_t vh_index(std::vector<REAL_> &f, size_t vh, size_t vg);

	void centroid(std::vector<REAL_> &vm, size_t vg);

	// ----------------------------------------------------------------------Bounded
	template<typename Function, typename Constraint>
	[[nodiscard]]REAL_ MinSearch(const Function &objfunc, const Constraint &constrain, PrintIterations print); //C-style. Canviar a C++

	// ----------------------------------------------------------------------Unbounded
	template<typename Function>
	[[nodiscard]]REAL_ MinSearch(const Function &objfunc, PrintIterations print) {
		return MinSearch(objfunc, [](const std::vector<REAL_> &x)->void {}, print);
	}

	std::vector<REAL_>   xvalues() { return start; }
};


template<size_t n>
void TNelderMead<n>::initialize_simplex()
{
	REAL_ pn, qn;   /* values used to create initial simplex */
	int     i, j;

	pn = scale * (sqrt(n + 1.0) - 1.0 + n) / (n*sqrt(2.0));
	qn = scale * (sqrt(n + 1.0) - 1.0) / (n*sqrt(2.0));

	for (i = 0; i < n; i++) {
		v[0][i] = start[i];
	}

	for (i = 1; i <= n; i++) {
		for (j = 0; j < n; j++) {
			if (i - 1 == j) {
				v[i][j] = pn + start[j];
			}
			else {
				v[i][j] = qn + start[j];
			}
		}
	}
}

// ------------------------------------------------------------------
template<size_t n>
void TNelderMead<n>::print_initial_simplex(const std::vector<REAL_> &f) const
{

	std::cout << "Valores Iniciales\n";
	for (size_t j = 0; j <= n; j++) {
		for (size_t i = 0; i < n; i++) {
			printf("%f, ", v[j][i]);
		}
		printf("value %f\n", f[j]);
	}
}

// ----------------------------------------------------------------
template<size_t n>
void TNelderMead<n>::print_iteration(const std::vector<REAL_> &f, int itr) const
{

	printf("Iteración %d\n", itr);
	for (size_t j = 0; j <= n; j++) {
		for (size_t i = 0; i < n; i++) {
			printf("%f %f\n", v[j][i], f[j]);
		}
	}
}

// ------------------------------------------------------------

/* find the index of the largest value */
template<size_t n>
size_t TNelderMead<n>::vg_index(std::vector<REAL_> &f, size_t vg)
{

	for (size_t j = 0; j <= n; j++) {
		if (f[j] > f[vg]) {
			vg = j;
		}
	}
	return vg;
}

// ---------------------------------------------------------------

/* find the index of the smallest value */
template<size_t n>
size_t TNelderMead<n>::vs_index(std::vector<REAL_> &f, size_t vs)
{
	int j;

	for (j = 0; j <= n; j++) {
		if (f[j] < f[vs]) {
			vs = j;
		}
	}
	return vs;
}

// -------------------------------------------------

/* find the index of the second largest value */
template<size_t n>
size_t TNelderMead<n>::vh_index(std::vector<REAL_> &f, size_t vh, size_t vg)
{
	int j;

	for (j = 0; j <= n; j++) {
		if (f[j] > f[vh] && f[j] < f[vg]) {
			vh = j;
		}
	}
	return vh;
}


// ----------------------------------------------------

/* calculate the centroid */
template<size_t n>
void TNelderMead<n>::centroid(std::vector<REAL_> &vm, size_t vg)
{
	double cent;

	for (size_t j = 0; j <= n - 1; j++) {
		cent = 0.0;
		for (size_t m = 0; m <= n; m++) {
			if (m != vg) {
				cent += v[m][j];
			}
		}
		vm[j] = cent / n;
	}
}

// --------------------------------------------------------

template<size_t n>
template<typename Function, typename Constraint>
REAL_ TNelderMead<n>::MinSearch(const Function &objfunc, const Constraint &constrain, PrintIterations print)
{
	size_t vs,  /* vertex with smallest value */
		   vh,  /* vertex with next smallest value */
		   vg;  /* vertex with largest value */

	size_t    j, row;
	          int  k,     /* track the number of function evaluations */
	             itr;	  /* track the number of iterations */

	REAL_              fr, /* value of function at reflection point */
		               fe, /* value of function at expansion point */
		               fc, /* value of function at contraction point */
					  min,
					 fsum,
		             favg,
		                s;

	std::vector<REAL_>  f(n+1), /* value of function at each vertex */
		                 vr(n), /* reflection - coordinates */
		                 ve(n), /* expansion - coordinates */
		                 vc(n), /* contraction - coordinates */
		                 vm(n); /* centroid - coordinates */


	/*Inicializaciones*/
	v.resize(n+1);
	for (auto &col:v)
		col.resize(n);


	/* create the initial simplex */
	initialize_simplex();

	/* impose constraints */
		for (j = 0; j <= n; j++) {
			constrain(v[j]);
		}

	/* find the initial function values */
	for (j = 0; j <= n; j++) {
		f[j] = objfunc(v[j]);
	}
	k = n + 1;

	/* print out the initial values */
	if(print)
	print_initial_simplex(f);

	/* begin the main loop of the minimization */
	for (itr = 1; itr <= MAX_IT; itr++) {
		/* find the index of the largest value */
		vg = vg_index(f, 0);

		/* find the index of the smallest value */
		vs = vs_index(f, 0);

		/* find the index of the second largest value */
		vh = vh_index(f, vs, vg);

		/* calculate the centroid */
		centroid(vm, vg);

		/* reflect vg to new vertex vr */
		for (j = 0; j <= n - 1; j++) {
			/*vr[j] = (1+ALPHA)*vm[j] - ALPHA*v[vg][j];*/
			vr[j] = vm[j] + ALPHA * (vm[j] - v[vg][j]);
		}

		constrain(vr);
		fr = objfunc(vr);
		k++;

		if (fr < f[vh] && fr >= f[vs]) {
			for (j = 0; j <= n - 1; j++) {
				v[vg][j] = vr[j];
			}
			f[vg] = fr;
		}

		/* investigate a step further in this direction */
		if (fr < f[vs]) {
			for (j = 0; j <= n - 1; j++) {
				/*ve[j] = GAMMA*vr[j] + (1-GAMMA)*vm[j];*/
				ve[j] = vm[j] + GAMMA * (vr[j] - vm[j]);
			}

			constrain(ve);
			fe = objfunc(ve);
			k++;

			/*
		   by making fe < fr as opposed to fe < f[vs],
		   Rosenbrocks function takes 63 iterations as opposed
		   to 64 when using double variables.
			*/

			if (fe < fr) {
				for (j = 0; j <= n - 1; j++) {
					v[vg][j] = ve[j];
				}
				f[vg] = fe;
			}
			else {
				for (j = 0; j <= n - 1; j++) {
					v[vg][j] = vr[j];
				}
				f[vg] = fr;
			}
		}

		/* check to see if a contraction is necessary */
		if (fr >= f[vh]) {
			if (fr < f[vg] && fr >= f[vh]) {
				/* perform outside contraction */
				for (j = 0; j <= n - 1; j++) {
					/*vc[j] = BETA*v[vg][j] + (1-BETA)*vm[j];*/
					vc[j] = vm[j] + BETA * (vr[j] - vm[j]);
				}

				constrain(vc);
				fc = objfunc(vc);
				k++;
			}
			else {
				/* perform inside contraction */
				for (j = 0; j <= n - 1; j++) {
					/*vc[j] = BETA*v[vg][j] + (1-BETA)*vm[j];*/
					vc[j] = vm[j] - BETA * (vm[j] - v[vg][j]);
				}

				constrain(vc);
				fc = objfunc(vc);
				k++;
			}


			if (fc < f[vg]) {
				for (j = 0; j <= n - 1; j++) {
					v[vg][j] = vc[j];
				}
				f[vg] = fc;
			}

			else {
				/*
				   at this point the contraction is not successful,
				   we must halve the distance from vs to all the
				   vertices of the simplex and then continue.
				   1997-10-31 - modified to account for ALL vertices.
				*/

				for (row = 0; row <= n; row++) {
					if (row != vs) {
						for (j = 0; j <= n - 1; j++) {
							v[row][j] = v[vs][j] + (v[row][j] - v[vs][j]) / 2.0;
						}
					}
				}

				/* re-evaluate all the vertices */
				for (j = 0; j <= n; j++) {
					f[j] = objfunc(v[j]);
				}

				/* find the index of the largest value */
				vg = vg_index(f, 0);

				/* find the index of the smallest value */
				vs = vs_index(f, 0);

				/* find the index of the second largest value */
				vh = vh_index(f, vs, vg);


				constrain(v[vg]);
				f[vg] = objfunc(v[vg]);
				k++;

				constrain(v[vh]);
				f[vh] = objfunc(v[vh]);
				k++;


			}
		}

		/* print out the value at each iteration */
		if(print)
		print_iteration(f,itr);

		/* test for convergence */
		fsum = 0.0;
		for (j = 0; j <= n; j++) {
			fsum += f[j];
		}
		favg = fsum / (n + 1);
		s = 0.0;
		for (j = 0; j <= n; j++) {
			s += pow((f[j] - favg), 2.0) / (n);
		}
		s = sqrt(s);
		if (s < eps) break;

		if (itr == MAX_IT) throw TXGen(u8"Límite de Iteraciones alcanzado", __func__);
	}
	/* end main loop of the minimization */

	/* find the index of the smallest value */
	vs = vs_index(f, 0);

	/*printf("The minimum was found at\n"); */
	for (j = 0; j < n; j++) {
		if(print)
		printf("%e\n",v[vs][j]);
		start[j] = v[vs][j];
	}
	min = objfunc(v[vs]);
	k++;
	if (print) 
	{
		printf("%d Function Evaluations\n", k);
		printf("%d Iterations through program\n", itr);
	}
	return min;
}

#endif
