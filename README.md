# Bumper-dataset
A self created dataset of road bumpers in IIT Kharagpur, for training CNNs that'd allow self driving cars to detect them.

It consists of 110 720p images, captured at various locations in IITKGP campus. Each of the images have a binary counterpart, in which the parts containing the bumpers are crudely marked in white

The file datamaker.cpp and the corresponding a.out would split the images into positive and negative samples, based on the percentage of white/black in them.

I've spent a lot of time making this, so if someone happens to use it, please do give credits. And in typical IITKGP lingo, peace!
