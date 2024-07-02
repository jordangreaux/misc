import pandas as pd

df = pd.read_csv('drug.csv')

# Features based on demographic qualities of respondents
dv_features = df[['PROVID', 
                  'DVGENDER', 
                  'DVURBAN', 
                  'DVRES', 
                  'DVORIENT', 
                  'DVDESCRIBE', 
                  'GH_020', 
                  'ALC_050']]

# Features regarding experiencing bullying in the past 30 days
bullied_features = df[['BUL_010', 
                       'BUL_020', 
                       'BUL_030', 
                       'BUL_040', 
                       'BUL_050', 
                       'BUL_060', 
                       'ALC_050']]

# Features regarding perpetrating bullying in the past 30 days
bully_features = df[['BUL_070',
                     'BUL_080',
                     'BUL_090',
                     'BUL_100',
                     'BUL_110',
                     'BUL_120',
                     'ALC_050']]

# Features regarding tobacco use in the past 30 days
tb_features = df[['TP_001',
                  'TP_016',
                  'TP_046',
                  'TP_056',
                  'TP_066',
                  'TP_086',
                  'ELC_026a',
                  'ELC_026b',
                  'ELC_026c',
                  'ALC_050']]

# Features regarding cannabis use in the past 30 days
can_features = df[['CAN_010',
                   'CAN_020',
                   'CAN_030',
                   'CAN_040',
                   'CAN_050',
                   'CAN_060',
                   'CAN_070',
                   'CAN_080',
                   'CAN_091',
                   'CAN_092',
                   'CAN_100',
                   'CAN_110',
                   'CAN_121',
                   'CAN_130',
                   'CAN_140',
                   'ALC_050']]