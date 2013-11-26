#ifndef COMP_LABELLER_INTERFACE_H
#define COMP_LABELLER_INTERFACE_H

// std
#include "opencv2/core/core.hpp"

/*! \class  CompLabellerInterface
 *
 */
class CompLabellerInterface {
public:
    typedef cv::Point Point;
    typedef std::vector<cv::Point> Comp;

    /*! constructor */
    CompLabellerInterface();

    /*!
     * Labels the connected components.
     * This can be the place for the first pass.
     * \param img the image to process
     */
    virtual void process_image(cv::Mat1b & img) = 0;

    /*!
     * \brief   returns all the list of points making all the connected components
     * of the image
     * This can be the place for the second pass.
     *
     * \param   img the monochrome image
     * \param   components_pts the vector of vector of points which will
     * contain the results
     * \param   boundingBoxes the bounding boxes of the points
     */
    virtual void get_connected_components
    (const int cols,
     std::vector< Comp > & components_pts,
     std::vector<cv::Rect> & boundingBoxes) = 0;


private:
};

#endif // COMP_LABELLER_INTERFACE_H
