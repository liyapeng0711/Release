//
// Copyright (c) 2009-2014 Shawn Singh, Glen Berseth, Mubbasir Kapadia, Petros Faloutsos, Glenn Reinman
// See license.txt for complete license.
//
/*
 * Obstacle.cpp
 * RVO2 Library
 *
 * Copyright (c) 2008-2010 University of North Carolina at Chapel Hill.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for educational, research, and non-profit purposes, without
 * fee, and without a written agreement is hereby granted, provided that the
 * above copyright notice, this paragraph, and the following four paragraphs
 * appear in all copies.
 *
 * Permission to incorporate this software into commercial products may be
 * obtained by contacting the authors <geom@cs.unc.edu> or the Office of
 * Technology Development at the University of North Carolina at Chapel Hill
 * <otd@unc.edu>.
 *
 * This software program and documentation are copyrighted by the University of
 * North Carolina at Chapel Hill. The software program and documentation are
 * supplied "as is," without any accompanying services from the University of
 * North Carolina at Chapel Hill or the authors. The University of North
 * Carolina at Chapel Hill and the authors do not warrant that the operation of
 * the program will be uninterrupted or error-free. The end-user understands
 * that the program was developed for research purposes and is advised not to
 * rely exclusively on the program for any reason.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE
 * AUTHORS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS
 * SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA AT
 * CHAPEL HILL OR THE AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY
 * DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY
 * STATUTORY WARRANTY OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS ON
 * AN "AS IS" BASIS, AND THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE
 * AUTHORS HAVE NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
 * ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Please send all bug reports to <geom@cs.unc.edu>.
 *
 * The authors may be contacted via:
 *
 * Jur van den Berg, Stephen J. Guy, Jamie Snape, Ming C. Lin, Dinesh Manocha
 * Dept. of Computer Science
 * 201 S. Columbia St.
 * Frederick P. Brooks, Jr. Computer Science Bldg.
 * Chapel Hill, N.C. 27599-3175
 * United States of America
 *
 * <http://gamma.cs.unc.edu/RVO2/>
 */

#include "Obstacle.h"
#include "obstacles/BoxObstacle.h"

Obstacle::Obstacle()
{
	isConvex_ = (false);
	nextObstacle_ = (NULL);
	prevObstacle_ = (NULL);
	id_ = (0);
}

Obstacle::~Obstacle()
{

}

void Obstacle::draw()
{
	// nothing to draw yet
}

std::pair<std::vector<Util::Point>,std::vector<size_t> > Obstacle::getStaticGeometry()
{
	std::pair<std::vector<Util::Point>,std::vector<size_t> > stuff;
	// get axis aligned box
	// make boxObstacle from it
	SteerLib::BoxObstacle * box = new SteerLib::BoxObstacle(_bounds.xmin, _bounds.xmax, _bounds.ymin, _bounds.ymax, _bounds.zmin, _bounds.zmax, 1.0f); /// TODO: Create support for all types of obstacles in scenarios
	stuff = box->getStaticGeometry();
	delete box;
	return stuff;
}

bool Obstacle::intersects(const Util::Ray &r, float &t)
{

	if (nextObstacle_)
	{
		Util::Point interP;
		if ( Util::intersect2Lines2D(this->point_, this->nextObstacle_->point_, r.pos, r.pos + (r.dir*r.maxt), interP) )
		{
			return true;
		}
	}
	if ( prevObstacle_)
	{
		Util::Point interP;
		if ( Util::intersect2Lines2D(this->point_, this->prevObstacle_->point_, r.pos, r.pos + (r.dir*r.maxt), interP) )
		{
			return true;
		}
	}
	return false;
}

float Obstacle::computePenetration(const Util::Point & p, float radius)
{
	return Util::computeBoxCirclePenetration2D(_bounds.xmin, _bounds.xmax, _bounds.zmin, _bounds.zmax, p, radius);
}
