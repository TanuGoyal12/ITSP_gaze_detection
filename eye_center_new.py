from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression

def normalize(data):
    mean = data.mean(axis=0)
    std = data.std(axis=0)
    data = (data-mean)/std
    return data,mean,std


def get_models(data):
    X = data[:,[0,1]]
    y_x = data[:,2]
    y_y = data[:,3]

    poly_features = PolynomialFeatures(degree=2,include_bias=False)
    X_poly = poly_features.fit_transform(X)
    X_poly_norm, mean, std = normalize(X_poly)

    lin_reg_x = LinearRegression()
    lin_reg_x.fit(X_poly_norm,y_x)
    
    lin_reg_y = LinearRegression()
    lin_reg_y.fit(X_poly_norm,y_y)

    return lin_reg_x, lin_reg_y
