#ifndef CPPEXTERNALEFFECTS_HH_
#define CPPEXTERNALEFFECTS_HH_



#include "Python.h"

#include "ExternalEffects.hh"
#include "BaseLaserFieldSource.hh"


using namespace TrackerRK4;

namespace LaserStripping{
	
	class  LasStripExternalEffects: public ExternalEffects
	{
		public:
		
			/** Constructor. */
			LasStripExternalEffects(OrbitUtils::BaseLaserFieldSource*	BaseLaserField, char *addressEG,int states);
			
			/** Destructor. */
			~LasStripExternalEffects();
		
		/** It initializes effects. */
		void setupEffects(Bunch* bunch);
		
		/** It finalizes effects. */
		void finalizeEffects(Bunch* bunch);

		/** It applies the external effects to a particle with certain index. */
		void applyEffects(Bunch* bunch, int index, 
	                            double* y_in_vct, double* y_out_vct, 
														  double t, double t_step, 
														  OrbitUtils::BaseFieldSource* fieldSource,
															RungeKuttaTracker* tracker);	
		

		
	
		

		

		  private:

		  
			  
			  OrbitUtils::BaseLaserFieldSource*	LaserField;
			  
			  //this array is used on each step of solution of density matrix equation at definite field  
			  tcomplex*** exp_mu_El;
			  tcomplex*** k_RungeKutt;
			  tcomplex*** mu_Elas;
			  double* Gamma_i;
			  double* E_i;
			  double** gamma_ij;
			  bool** cond;

			  
			  int levels;
			  
		  
			  //Parameters of orientation of laser in space
			  double param1;
			  double param2;
			  double param3;
			  double param4;
			  
			 
			  //time and frequensy of laser in frame of particle
			  double omega_part;
			  double part_t_step;
			  double t_part;
			  double phasa_part;
			  					  
			  //Fields in the particle frame  
			  tcomplex Ex_las[3];
			  tcomplex Ey_las[3];
			  tcomplex Ez_las[3];
			  
			  tcomplex Bx_las[3];
			  tcomplex By_las[3];
			  tcomplex Bz_las[3];
			  
			  double Ex_stat;
			  double Ey_stat;
			  double Ez_stat;
			  
			  double Bx_stat;
			  double By_stat;
			  double Bz_stat;
			  			 

			  
			  			  	
				/**Solver for Amplitudes**/
				void AmplSolver4step(int i,Bunch* bunch);
							
				/*this all parameters in frame of particle in atomic units necesarry for applying external effect  */
				void GetFrameParticleParameters(int i, double t, double t_step, Bunch* bunch);
				
				/*this method gives laser and static fields transformed by rotation relatively z axes  */
				void GetFrameParticleFields(int i, double t,  Bunch* bunch,  OrbitUtils::BaseFieldSource* fieldSource);
				
				/*This method provides rotational transformation of statis and laser field in frame of particle to z axes */
				double	RotateElectricFields(double Ex_s, double Ey_s, double Ez_s,tcomplex& Ex_l,tcomplex& Ey_l,tcomplex& Ez_l);
				

				
	};
};



#endif /*CPPEXTERNALEFFECTS_HH_*/


