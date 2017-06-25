// MovieRatingWithArrays.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;


const double REVIEWER_RATINGS[5][6] = { { 100, 101, 102, 103, 104, 105 },
									 { 3,1,5,2,1,5 },
									 { 4,2,1,4,2,4 },
									 { 3,1,2,4,4,1 },
									 { 5,1,4,2,4,2 }
								   };
const int NUM_USER_RATINGS = 3;
const int TOT_NUM_MOVIES = 6;
const int NUM_REVIEWERS = 4;


void getUserRatings(int userRatings[], int moviesChosen[], int numberOfRatings);
//Preconditions: number of ratings is less than or equal to 6
//post condition: userRatings[] is filled with ratings on the specified movies and moviesChosen[] is filled with the specified movies

void printUserRatingsAndMovieChoices(int userRatings[], int moviesChosen[], int numberOfRatings);

int getClosestProReviewer(int userRatings[], int moviesChosen[], int numberOfRatings);
//Precondition: userRatings[] is filled with ratings and moviesChosen[] is filled with the associated movies
//Post condition: the reviewer with the closest review pattern is returned

void printClosestReviewerAndMovieList(int closestProReviewer);
//PreCondiiton: closest pro reviewer is a number from 1 to NUM_REVIEWERS
//PostCondition: the closest pro reviewer is printed to the console along with thier movie rating list


int main()
{
	
	int userRatings[NUM_USER_RATINGS] = {0,0,0};
	int moviesChosen[NUM_USER_RATINGS] = {0,0,0};
	int closestProReviewer = 1000;

	bool keepRating = true;
	char yesOrNo;

	while (keepRating == true)
	{
		getUserRatings(userRatings, moviesChosen, NUM_USER_RATINGS);
		printUserRatingsAndMovieChoices(userRatings, moviesChosen, NUM_USER_RATINGS);
		closestProReviewer = getClosestProReviewer(userRatings, moviesChosen, NUM_USER_RATINGS);
		printClosestReviewerAndMovieList(closestProReviewer);
		cout << "Review Again? (Y/N): ";
		cin >> yesOrNo;
		cout << endl;

		if (yesOrNo == 'N' || yesOrNo == 'n')
			keepRating = false;
	}

	return 0;
}

void getUserRatings(int userRatings[], int moviesChosen[], int numberOfRatings)
{
	for (int i = 0; i < numberOfRatings; i++)
	{
		cout << "Enter the number of the movie you would like to rate (100, 101, 102, 103, 104, 105): ";
		cin >> moviesChosen[i];
		cout << endl;
		cout << "Please rate movie " << moviesChosen[i] << " on a scale from 1 to 5: ";
		cin >> userRatings[i];
		cout << endl;
	}	
	return;
}

void printUserRatingsAndMovieChoices(int userRatings[], int moviesChosen[], int numberOfRatings)
{
	for (int i = 0; i < numberOfRatings; i++)
	{
		cout << "Movie choice: " << moviesChosen[i] << " User Rating: " << userRatings[i];
		cout << endl;
	}
	return;
}

int getClosestProReviewer(int userRatings[], int moviesChosen[], int numberOfRatings)
{
	int closeProReviewer = 30;
	double closeReviewerDistance = 30;

	
	double currentReviewDistance;
	int currentMovieIndex;


	for (int i = 1; i < NUM_REVIEWERS; i++)
	{
		currentReviewDistance = 0;
		for (int j = 0; j < numberOfRatings; j++)
		{
			currentMovieIndex = moviesChosen[j] - 100;
			currentReviewDistance += pow(static_cast<double>(userRatings[j] - REVIEWER_RATINGS[i][currentMovieIndex]), 2.0);
		}
		currentReviewDistance = sqrt(currentReviewDistance);

		if (currentReviewDistance < closeReviewerDistance)
		{
			closeReviewerDistance = currentReviewDistance;
			closeProReviewer = i;
		}
	}


	return closeProReviewer;
}

void printClosestReviewerAndMovieList(int closestProReviewer)
{
	cout << "The closest reviewer was: " << closestProReviewer; 
	cout << " Their Reviews of movies 100 through 105 were: ";
	for (int i = 0; i < TOT_NUM_MOVIES; i++)
	{
		cout << REVIEWER_RATINGS[closestProReviewer][i] << " ";
	}
	cout << endl;
	cout << "Thank you for Reviewing! \n";
	return;
}
