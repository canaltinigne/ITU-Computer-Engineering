% Learning From Data - HW1
% Q4 - KNN Classifier
% Team: Feeding with My Hands
% Can Yilmaz Altinigne - 150130132
% Mehmet Baris Yaman - 150130136

% First add the hw1.mat file by opening it and clicking finish.

% You can change K value from here !

K = 5;

row_number = size(d,1);

% Since the given dataset is all y=0 after that y=1
% We shuffle the dataset
randomized_arr = d(randperm(size(d,1)),:);

% First 80% of dataset is training set
% and column of zeros is added to dataset to use for distance value later
training_set = randomized_arr(1:0.8*row_number, :);
training_set = [training_set zeros(size(training_set,1),1)];

% Last 20% of dataset is test set
test_set = randomized_arr(0.8*row_number + 1:row_number, :);

% Predicted set is created
predicted_set = test_set(:,:);

% Traverse all test set datas
for i = 1:0.2*row_number
    
    % Find the test point data's distance to all training set points
    % and set that value for training set's 4th column which we added 
    % before
    for z = 1:0.8*row_number
        diff = (test_set(i,1)-training_set(z,1))^2 + (test_set(i,2)-training_set(z,2))^2;
        training_set(z, 4) = diff;
    end
    
    % Closest K neighbors are found by finding sorted training set data
    % by the distance from that test data, First K rows are taken.
    
    closest_K_neighbors = sortrows(training_set, 4);
    closest_K_neighbors = closest_K_neighbors(1:K, :);
    
    % Third column is the dependent variable of training set
    % Since the value can be 0 or 1. Sum them and check if it is
    % bigger than K/2
    % if it's then predicted value for that test set data is 1 else it's 0.
    
    sum_of_ones = sum(closest_K_neighbors(:,3));
    
    if sum_of_ones > K/2
        predicted_set(i,3) = 1;
    else
        predicted_set(i,3) = 0;
    end
end

colors = [[0 0 1]; [1 0 0]];    % Blue for 0, Red for 1
colors(1, :);

colormat_pred = colors(predicted_set(:,3)+1, :);
colormat_test = colors(test_set(:,3)+1, :);

% Show the Figures

scatter(predicted_set(:,1), predicted_set(:,2), 20, colormat_pred, 'filled')
title('KNN5 Results      -     Class 0: Blue, Class 1: Red')
xlabel('X1')
ylabel('X2')
figure
scatter(test_set(:,1), test_set(:,2), 20, colormat_test, 'filled')
title('Real Test Set Results      -     Class 0: Blue, Class 1: Red')
xlabel('X1')
ylabel('X2')

% Find the Correct Predictions
correct_pred = 0;

for t = 1:0.2*row_number
    if predicted_set(t,3) == test_set(t,3)
        correct_pred = correct_pred + 1;
    end
end

sprintf('KNN5\nCorrect Predictions: %d \nWrong Predictions: %d\nAccuracy: %.2f%%', correct_pred, 0.2*row_number-correct_pred, 100*correct_pred/(0.2*row_number))

% Same thing for K = 3
K = 3

% Traverse all test set datas
for i = 1:0.2*row_number
    
    % Find the test point data's distance to all training set points
    % and set that value for training set's 4th column which we added 
    % before
    for z = 1:0.8*row_number
        diff = (test_set(i,1)-training_set(z,1))^2 + (test_set(i,2)-training_set(z,2))^2;
        training_set(z, 4) = diff;
    end
    
    % Closest K neighbors are found by finding sorted training set data
    % by the distance from that test data, First K rows are taken.
    
    closest_K_neighbors = sortrows(training_set, 4);
    closest_K_neighbors = closest_K_neighbors(1:K, :);
    
    % Third column is the dependent variable of training set
    % Since the value can be 0 or 1. Sum them and check if it is
    % bigger than K/2
    % if it's then predicted value for that test set data is 1 else it's 0.
    
    sum_of_ones = sum(closest_K_neighbors(:,3));
    
    if sum_of_ones > K/2
        predicted_set(i,3) = 1;
    else
        predicted_set(i,3) = 0;
    end
end

colors = [[0 0 1]; [1 0 0]];    % Blue for 0, Red for 1
colors(1, :);

colormat_pred = colors(predicted_set(:,3)+1, :);
colormat_test = colors(test_set(:,3)+1, :);

% Show the Figures

figure

scatter(predicted_set(:,1), predicted_set(:,2), 20, colormat_pred, 'filled')
xlabel('X1')
ylabel('X2')
title('KNN3 Results     -     Class 0: Blue, Class 1: Red')

% Find the Correct Predictions
correct_pred = 0;

for t = 1:0.2*row_number
    if predicted_set(t,3) == test_set(t,3)
        correct_pred = correct_pred + 1;
    end
end

sprintf('KNN3\nCorrect Predictions: %d \nWrong Predictions: %d\nAccuracy: %.2f%%', correct_pred, 0.2*row_number-correct_pred, 100*correct_pred/(0.2*row_number))