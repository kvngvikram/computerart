#!/usr/bin/env python
from fortran_subroutines import julia_set_complex_polinomial
import matplotlib.pyplot as plt

# These used only in save_image() function
from PIL import Image
from matplotlib.cm import hot as my_cmap
import numpy as np

c = -0.512511498387847167 + 0.521295573094847167j
p = 2
min_x = -1.8
max_x = 1.8
center_y = 0
# aspect_ratio = 16/9
aspect_ratio = 4/3
x_res = 480
# x_res = 640
# x_res = 1920
zoom_scale = 0.3
escape_rad = 4
max_iter = 300

image_file_name = 'image.png'

min_y = center_y - (max_x - min_x)/(2*aspect_ratio)
max_y = center_y + (max_x - min_x)/(2*aspect_ratio)
y_res = int(x_res/aspect_ratio)


def replot(min_x, max_x, min_y, max_y, axis):
    data = julia_set_complex_polinomial(
        min_x, max_x, min_y, max_y, x_res, y_res, c, p, max_iter, escape_rad)
    axis.clear()
    axis.imshow((data), extent=[min_x, max_x, min_y, max_y],
                cmap=my_cmap)
    ax.set_xlabel('Real axis')
    ax.set_ylabel('Imaginary axis')
    axis.set_title('$n$ in $Z_{n+1}=Z_n^P + C$ \n\n'
                   + 'C ='
                   + '{:0.2f}'.format(c.real) + '+' + '{:0.2f}'.format(c.imag)
                   + 'i' + ', P ='
                   + '{:0.2f}'.format(p.real) + '+' + '{:0.2f}'.format(p.imag)
                   + 'i' + ', Escape radius = ' + str(escape_rad)
                   + ', Max iterations = ' + str(max_iter))
    plt.draw()  # this is required

    return data


fig, ax = plt.subplots()
ax.set_xlabel('Real axis')
ax.set_ylabel('Imaginary axis')

data = replot(min_x, max_x, min_y, max_y, ax)


def save_image():
    im = Image.fromarray(np.uint8(my_cmap(data/data.max())*255))
    im.save(image_file_name)


def resize(event):
    if event.inaxes is not None:
        axis = event.inaxes
        min_x, max_x = axis.get_xlim()  # l,h for lower and higher
        min_y, max_y = axis.get_ylim()
        c_x, c_y = event.xdata, event.ydata  # mouse pointer locations on axis
        new_min_x = min_x + (2*(event.button == 'up')-1)*(c_x-min_x)*zoom_scale
        new_max_x = max_x + (2*(event.button == 'up')-1)*(c_x-max_x)*zoom_scale
        new_min_y = min_y + (2*(event.button == 'up')-1)*(c_y-min_y)*zoom_scale
        new_max_y = max_y + (2*(event.button == 'up')-1)*(c_y-max_y)*zoom_scale

        replot(new_min_x, new_max_x, new_min_y, new_max_y, axis)


def click(event):
    axis = event.inaxes
    if(event.button == 1 and event.dblclick):
        replot(min_x, max_x, min_y, max_y, axis)
    elif(event.button == 1 and not event.dblclick):
        present_min_x, present_max_x = axis.get_xlim()
        present_min_y, present_max_y = axis.get_ylim()
        print('{:0.2e}'.format(present_min_x) + '\t' +
              '{:0.2e}'.format(present_max_x) + '\t' +
              '{:0.2e}'.format(present_min_y) + '\t' +
              '{:0.2e}'.format(present_max_y) + '\t' +
              '{:0.2f}'.format(c.real)+'+'+'{:0.2f}'.format(c.imag) + 'i\t' +
              '{:0.2f}'.format(p.real)+'+'+'{:0.2f}'.format(p.imag) + 'i\t')
    elif(event.button > 1):
        save_image()


cid1 = fig.canvas.mpl_connect('scroll_event', resize)
cid2 = fig.canvas.mpl_connect('button_press_event', click)
print('Scroll to zoom, double click to go to default ranges, right click to \
        save as image.')
print('Single click to get:')
print('min_x\tmax_x\tmin_y\tmax_y\tc\tp')


fig.tight_layout()
mng = plt.get_current_fig_manager()
mng.window.showMaximized()
plt.show()
