# cpisoFoam
A fork of pisoFoam in order to calculate concentration field in the case of two-stream mixing

The concentration transport is calculated through the transport equation of Mixture-fraction
It can be found  in the book Computational Models for Turbulent Reacting Flows by Rodney O. Fox
The transport equation of Mixture-fraction Ksi and its variance is from the work done by Liu Ying (2006)

The variance of mixture-fraction is under the assumption that sub-grid scale concentration distribution follows Beta-distribution

The initial goal of this solver is to solve simple chemical reaction in liquid phase (It may be not suitable for gas phase)

