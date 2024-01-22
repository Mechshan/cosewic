# Canada Species at Risk Analysis Program implemented in C


## Overview

This Program is a tool designed for analyzing and presenting data on species at risk across Canada. This program processes fictionalized data from a file of simulated trends and statuses of various species.

## Features

The program offers several viewing options to analyze the data:

1. View by Year: Displays data sorted in ascending order by year.
2. View by Province: Shows information sorted in descending order by total counts per province.
3. View by Taxon: Presents data sorted in ascending order by total counts per taxon.
4. View by Province and Taxon: Allows a more granular view, filtering data based on a specific province and taxon.

Each view provides a detailed breakdown of species at risk, categorized under different statuses: Extinct, Extirpated, Endangered, Threatened, and Concern.

## Data Structure and Handling

The data is loaded from a file and organized into a tabular format with the following columns:

- Extinct
- Extirpated
- Endangered
- Threatened
- Concern
- Total

## Sorting and Data Manipulation

The application implements the Quicksort algorithm (as per Lomuto partition scheme) to sort analysis tables.

## Images

![image1](/images/img0.JPG)

![image2](/images/img1.JPG)