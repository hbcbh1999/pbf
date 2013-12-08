#ifndef SIMULATION_H
#define SIMULATION_H

#include "common.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Framing.h"
#include "Font.h"
#include "Icosahedron.h"

/** Simulation class.
 * This is the main class which takes care of the whole simulation.
 */
class Simulation
{
public:
    /** Constructor.
     */
    Simulation (void);
    /** Destructor.
     */
    ~Simulation (void);

    /** Mouse movement event.
     * Handles mouse movement events.
     * \param x relative movement of the cursor in x direction
     * \param y relative movement of the cursor in y direction
     */
    void OnMouseMove (const double &x, const double &y);

    /** Resize event.
     * Handles window resize event.
     * \param width new framebuffer width
     * \param height new framebuffer height
     */
    void Resize (const unsigned int &width, const unsigned int &height);

    /** Animation loop.
     * This function is called every frame and performs the actual simulation.
     */
    void Frame (void);
private:
    /** Camera.
     * Used to handle input events and create a view matrix.
     */
    Camera camera;

    /** Surrounding shader program.
     * Shader program for displaying the surrounding scene.
    */
    ShaderProgram surroundingprogram;

    /** Particle shader program.
     * Shader program for displaying the particles.
    */
    ShaderProgram particleprogram;

    /** Framing.
     * Takes care of rendering a framing for the scene.
     */
    Framing framing;

    /** Icosahedron.
     * Model data of a regular icosahedron.
     */
    Icosahedron icosahedron;

    union {
        struct {
            /** Position buffer.
             * Buffer in which the particle positions are stored.
             */
            GLuint positionbuffer;

            /** Transformation uniform buffer.
             * Buffer object to store the projection and view matrix.
             */
            GLuint transformationbuffer;

            /** Lighting uniform buffer.
             * Buffer object to store the lighting parameters.
             */
            GLuint lightingbuffer;
        };
        /** Buffer objects.
         * The buffer objects are stored in a union, so that it is possible
         * to create/delete all buffer objects with a single OpenGL call.
         */
        GLuint buffers[3];
    };

    /** Font subsystem.
     * Takes care of displaying text.
     */
    Font font;

    /** Projection matrix.
     * Matrix describing the perspective projection.
     */
    glm::mat4 projmat;

    /** Framebuffer width.
     * Width of the current framebuffer.
     */
    unsigned int width;
    /** Framebuffer height.
     * Height of the current framebuffer.
     */
    unsigned int height;

    /** Last FPS time.
     * Stores the last time the fps count was updated.
     */
    float last_fps_time;
    /** Frame counter.
     * Frame counter used to determine the frames per second.
     */
    unsigned int framecount;
    /** Frames per second.
     * The number of frames rendered in the last second.
     */
    unsigned int fps;
};

#endif /* SIMULATION_H */
