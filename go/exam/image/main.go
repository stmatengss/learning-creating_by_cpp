package main

import "golang.org/x/tour/pic"

import (
	"image"
	"image/color"
)

type Image struct{
	W int
	H int
}

func (im Image) Bounds() image.Rectangle {
	return image.Rect(0, 0, im.W, im.H)
}

func (im Image) ColorModel() color.Model {
	return color.RGBAModel
}

func (im Image) At(x int, y int) color.Color {
	return color.RGBA{10, 10, 10, 10}
}

func main() {
	m := Image{128, 128}
	pic.ShowImage(m)
}
