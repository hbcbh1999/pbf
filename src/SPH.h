#ifndef SPH_H
#define SPH_H

#include "common.h"
#include "ShaderProgram.h"
#include "NeighbourCellFinder.h"
#include "RadixSort.h"

/** SPH class.
 * This class is responsible for the SPH simulation.
 */
class SPH
{
public:
	/** Constructor.
	 * \param numparticles number of particles in the simulation
	 */
	SPH (const GLuint &numparticles);
	/** Destructor.
	 */
	~SPH (void);

	/** Get particle buffer.
	 * Returns a buffer object containing the particle information.
	 * \returns the particle buffer
	 */
	GLuint GetParticleBuffer (void) const {
		return radixsort.GetBuffer ();
	}
	/** Get auxiliary buffer.
	 * Returns a buffer object containing auxiliary information for the
	 * particles coded as 4 component color values.
	 * \returns the auxiliary buffer
	 */
	const GLuint &GetAuxiliaryBuffer (void) const {
		return auxbuffer;
	}

	/** Check vorticity confinement.
	 * Checks the state of the vorticity confinement.
	 * \returns True, if vorticity confinement is enabled, false, if not.
	 */
	const bool &IsVorticityConfinementEnabled (void) const {
		return vorticityconfinement;
	}
	/** Enable/disable vorticity confinement.
	 * Specifies whether to use vorticity confinement or not.
	 * \param flag Flag indicating whether to use vorticity confinement.
	 */
	void SetVorticityConfinementEnabled (const bool &flag) {
		vorticityconfinement = flag;
	}

	/** Run simulation.
	 * Runs the SPH simulation.
	 */
	void Run (void);

	/** Output timing information.
	 * Outputs timing information about the simulation steps to the
	 * standard output.
	 */
	void OutputTiming (void);
private:

    /** Simulation step shader program.
     * Shader program for the simulation step that predicts the new position
     * of all particles.
     */
    ShaderProgram predictpos;

    /** Simulation step shader program.
     * Shader program for the simulation step that performs the solver iteration for each particle.
     */
    ShaderProgram solver;

    /** Vorticity program.
     * Shader program for calculating particle vorticity.
     */
    ShaderProgram vorticityprog;


    /** Neighbour Cell finder.
     * Takes care of finding neighbour cells for the particles.
     */
    NeighbourCellFinder neighbourcellfinder;

    /** Vorticity confinement flag.
     * flag indicating whether vorticity confinement should be used.
     */
    bool vorticityconfinement;

    /** Radix sort.
     * Takes care of sorting the particle list.
     * The contained buffer object is used as particle buffer.
     */
    RadixSort radixsort;

    union {
        struct {
        	/* The buffer object in radixsort is used as particle buffer*/

            /** Lambda buffer.
             * Buffer in which the specific scalar values are stored during the simulation steps.
             */
            GLuint lambdabuffer;

            /** Auxiliary buffer.
             * Buffer in which auxiliary data used for debugging purposes can be stored.
             */
            GLuint auxbuffer;

        };
        /** Buffer objects.
         * The buffer objects are stored in a union, so that it is possible
         * to create/delete all buffer objects with a single OpenGL call.
         */
        GLuint buffers[2];
    };

    union {
    	struct {
    		/** Preparation query object.
    		 * Query object to record the time spent in the preparation phase.
    		 */
    		GLuint preparationquery;
    		/** Predict position query object.
    		 * Query object to record the time spent in the predict position phase.
    		 */
    		GLuint predictposquery;
    		/** Sorting query object.
    		 * Query object to record the time spent in the sorting phase.
    		 */
    		GLuint sortquery;
    		/** Neighbour cell query object.
    		 * Query object to record the time spent in the neighbour cell phase.
    		 */
    		GLuint neighbourcellquery;
    		/** Solver query object.
    		 * Query object to record the time spent in the solver phase.
    		 */
    		GLuint solverquery;
    		/** Vorticity query object.
    		 * Query object to record the time spent in the vorticity confinement phase.
    		 */
    		GLuint vorticityquery;
    	};
        /** Query objects.
         * The query objects are stored in a union, so that it is possible
         * to create/delete all buffer objects with a single OpenGL call.
         */
        GLuint queries[6];
    };


    /** Number of particles.
     * Stores the number of particles in the simulation.
     */
    const GLuint numparticles;
};

#endif /* SPH_H */