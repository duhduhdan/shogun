/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Copyright (C) 2012 Jacob Walker
 */

#ifndef CSTUDENTSTLIKELIHOOD_H_
#define CSTUDENTSTLIKELIHOOD_H_

#include <shogun/regression/gp/LikelihoodModel.h>

namespace shogun
{

/** @brief This is the class that models a Gaussian Likelihood
 *
 * In this case, P(y|f) is normally distributed with mean f and
 * variance $\sigma$.
 *
 */
class CStudentsTLikelihood: public CLikelihoodModel
{

public:

	/*Constructor*/
	CStudentsTLikelihood();

	/*Destructor*/
	virtual ~CStudentsTLikelihood();

	/** Returns the name of the SGSerializable instance.  It MUST BE
	 *  the CLASS NAME without the prefixed `C'.
	 *
	 * @return name of the SGSerializable
	 */
	inline virtual const char* get_name() const { return "GaussianLikelihood"; }

	/** Returns the noise variance
	 *
	 * @return noise variance
	 */
	float64_t get_sigma() {return m_sigma;}

	/** Sets the noise variance
	 *
	 * @param s noise variance
	 */
	void set_sigma(float64_t s) {m_sigma = s;}

	/** Evaluate means
	 *
	 * @param Vector of means calculated by inference method
	 * @return Final means evaluated by likelihood function
	 */
	virtual SGVector<float64_t> evaluate_means(SGVector<float64_t>& means);

	/** Evaluate variances
	 *
	 * @param Vector of variances calculated by inference method
	 * @return Final variances evaluated by likelihood function
	 */
	virtual SGVector<float64_t> evaluate_variances(SGVector<float64_t>& vars);

	/** get model type
	  *
	  * @return model type Gaussian
	 */
	virtual ELikelihoodModelType get_model_type() {return LT_GAUSSIAN;}

	virtual float64_t get_log_probability_f(CRegressionLabels* labels, Eigen::VectorXd f);
	virtual Eigen::VectorXd get_log_probability_derivative_f(CRegressionLabels* labels, Eigen::VectorXd f, index_t i);
	virtual Eigen::VectorXd get_first_derivative(CRegressionLabels* labels, TParameter* param, CSGObject* obj, Eigen::VectorXd function);
	virtual Eigen::VectorXd get_second_derivative(CRegressionLabels* labels, TParameter* param, CSGObject* obj, Eigen::VectorXd function);

private:
	/** Observation noise sigma */
	float64_t m_sigma;

	float64_t m_df;

	/*Initialize function*/
	void init();

	float64_t dlgamma(float64_t x)
	{
	  x = x+6.0;
	  float64_t df = 1./(x*x);
	  df = (((df/240-0.003968253986254)*df+1/120.0)*df-1/120.0)*df;
	  df = df+log(x)-0.5/x-1.0/(x-1.0)-1.0/(x-2.0)-1.0/(x-3.0)-1.0/(x-4.0)-1.0/(x-5.0)-1.0/(x-6.0);
	  return df;
	}
};

}

#endif /* CStudentsTLIKELIHOOD_H_ */