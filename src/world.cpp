// world.cpp


#include "world.h"
#include "lander.h"
#include "ll.h"
#include "gpuProgram.h"
#include "strokefont.h"

#include <sstream>
#include <iomanip>

//const float textAspect = 0.7;	// text width-to-height ratio (you can use this for more realistic text on the screen)

float crashRadius = 0.0;
struct timeb newTime;
float runTime;

void World::updateState( float elapsedTime )

{
  // See if any keys are pressed for thrust

  if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS) // right arrow
    lander->rotateCW( elapsedTime );

  if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS) // left arrow
    lander->rotateCCW( elapsedTime );

  if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS) // down arrow
    lander->addThrust( elapsedTime );

  // Update the position and velocity

  lander->updatePose( elapsedTime );
  

  // See if the lander has touched the terrain

  vec3 closestTerrainPoint = landscape->findClosestPoint( lander->centrePosition() );
  float closestDistance = ( closestTerrainPoint - lander->centrePosition() ).length();

  // Find if the view should be zoomed

  zoomView = (closestDistance < ZOOM_RADIUS);

  // Check for landing or collision and let the user know
  //
  // Landing is successful if the vertical speed is less than 1 m/s and
  // the horizontal speed is less than 0.5 m/s.

  // YOUR CODE HERE
  crashRadius = (lander->width / 2) + 0.5;
  
  if(closestDistance < crashRadius)
  {
  	if (((abs(lander->velocity.x) <= 0.5) && (abs(lander->velocity.y) <= 1.0)))
  	{
  	  // SUCCESSFUL LANDING !!!
  		pauseGame = true;
  		world->showMsg = "SUCCESSFUL LANDING";
  	}
  	else
  	{
  	  // CRASH LANDING !!!
  		pauseGame = true;
  		world->showMsg = "CRASH LANDING";
  	}
  }
}

int World::getAltitudeOfLanderFromLandscape()
{
	// Find the distance to the point on the landscape directly below the lander
	float landerx = lander->centrePosition().x;
	float landery = lander->centrePosition().y;
	
	// find the segment that is directly below the lander
	vec4 segUnderLander = landscape->segmentUnderLander(lander->centrePosition());
	
	// Points that define the line under the lander
	float segmentStartX = segUnderLander.x;
	float segmentStartY = segUnderLander.y;
	float segmentEndX		= segUnderLander.z;
	float segmentEndY   = segUnderLander.w;
	
	// Calculate the ratio needed to find the point on the line
	float ratio = (landerx - segmentStartX) / (segmentEndX - segmentStartX);
	
	// Find the Y value of that point
	float pointOnSegmentY = ((segmentEndY - segmentStartY) * ratio) + segmentStartY;
	
	// Return difference in Y coord between the lander and the point on the segment
	float alt = landery - pointOnSegmentY;
	
	return alt;
}


void World::draw()
{
  mat4 worldToViewTransform;

  if (!zoomView) {

    // Find the world-to-view transform that transforms the world
    // to the [-1,1]x[-1,1] viewing coordinate system, with the
    // left edge of the landscape at the left edge of the screen, and
    // the bottom of the landscape BOTTOM_SPACE above the bottom edge
    // of the screen (BOTTOM_SPACE is in viewing coordinates).

    float s = 2.0 / (landscape->maxX() - landscape->minX());

    worldToViewTransform
      = translate( -1, -1 + BOTTOM_SPACE, 0 )
      * scale( s, s, 1 )
      * translate( -landscape->minX(), -landscape->minY(), 0 );

  } else {

    // Find the world-to-view transform that is centred on the lander
    // and is 2*ZOOM_RADIUS wide (in world coordinates).

    // YOUR CODE HERE
    
    float s = 2.0/(2*ZOOM_RADIUS);

    worldToViewTransform
      = translate( -1, -1 + BOTTOM_SPACE, 0 )
      * scale( s, s, 1 )
      * translate(ZOOM_RADIUS-lander->centrePosition().x,ZOOM_RADIUS-lander->centrePosition().y, 0 );
      
  }

  // Draw the landscape and lander, passing in the worldToViewTransform
  // so that they can append their own transforms before passing the
  // complete transform to the vertex shader.

  landscape->draw( worldToViewTransform );
  lander->draw( worldToViewTransform );
  
  // Draw the heads-up display (i.e. all text).
  stringstream title;
  title.setf( ios::fixed, ios::floatfield );
  title << "LUNAR LANDER ";
  drawStrokeString( title.str(), -.35, 0.70, 0.04, glGetUniformLocation( myGPUProgram->id(), "MVP") );

  // YOUR CODE HERE (modify the above code, too)
  
  stringstream ss;
  ss.setf( ios::fixed, ios::floatfield );
  ss.precision(1);
  ss << "SCORE: " << world->score ;
  drawStrokeString( ss.str(), -0.95, 0.70, 0.04, glGetUniformLocation( myGPUProgram->id(), "MVP") );
  
  //Calculate the amount of seconds since the program started
  ftime( &newTime );
  
  // if the game is paused stop the timer
  if (!pauseGame)
  {
  	runTime = (newTime.time + newTime.millitm / 1000.0) - (startTime.time + startTime.millitm / 1000.0);
  }
  
  // ADD TIME TO SCREEN
  stringstream t;
  t.setf( ios::fixed, ios::floatfield );
  t.precision(0);
  t << "TIME:  " <<runTime;
  drawStrokeString( t.str(), -0.95,0.65,0.04, glGetUniformLocation( myGPUProgram->id(), "MVP") );

  // ADD FUEL TO SCREEN
  stringstream f;
  f.setf( ios::fixed, ios::floatfield );
  f.precision(0);
  f << "FUEL:  " << lander->fuel;
  drawStrokeString( f.str(), -0.95,0.60, 0.04, glGetUniformLocation( myGPUProgram->id(), "MVP") );
  
  // ADD ALTITUDE TO SCREEN
  stringstream alt;
  alt.setf( ios::fixed, ios::floatfield );
  alt.precision(0);
  alt << "ALTITUDE:         " << world->getAltitudeOfLanderFromLandscape();
  drawStrokeString( alt.str(), 0.25, 0.70, 0.04, glGetUniformLocation( myGPUProgram->id(), "MVP") );
  
  // ADD Horizontal Speed TO SCREEN
  stringstream hs;
  hs.setf( ios::fixed, ios::floatfield );
  hs.precision(0);
  hs << "HORIZONTAL SPEED: " << abs(lander->velocity.x);
  drawStrokeString( hs.str(), 0.25, 0.65, 0.04, glGetUniformLocation( myGPUProgram->id(), "MVP") );
  
  // ADD Vertical Speed TO SCREEN
  stringstream vs;
  vs.setf( ios::fixed, ios::floatfield );
  vs.precision(0);
  vs << "VERTICAL SPEED:   " << abs(lander->velocity.y);
  drawStrokeString( vs.str(), 0.25, 0.60, 0.04, glGetUniformLocation( myGPUProgram->id(), "MVP") );
  
  stringstream endGame;
  endGame.setf( ios::fixed, ios::floatfield );
  endGame << showMsg;
  drawStrokeString( endGame.str(), -0.35, 0.2, 0.04, glGetUniformLocation( myGPUProgram->id(), "MVP") );

}
