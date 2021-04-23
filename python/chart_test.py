
# *_* coding= utf-8 *_*

import xlsxwriter

workbook = xlsxwriter.Workbook('chart.xlsx')
worksheet = workbook.add_worksheet()

bold = workbook.add_format({'bold': 1})
# Create a new Chart object.
chart = workbook.add_chart({'type': 'column'})
chart.set_size({"width": 800, "height": 400})
chart.set_title({"name": "stable test chart (10_0_30 mean 10 users continuously "
                         "send requests without delay for 30 seconds"})

# Write some data to add to plot on the chart.
data = [
    [1.1, 2.2, 3.3, 4.4, 5.5, 1.1, 2.2, 3.3, 4.4, 5.5],
    [2.1, 4.2, 6.3, 8.4, 10.5, 2.1, 4.2, 6.3, 8.4, 10.5],
    [3.1, 6.2, 9.3, 12.4, 15.5, 3.1, 6.2, 9.3, 12.4, 15.5]
]
row_name = ["", "one", "two", "three", "four", "five"]
col_name = ["", "10_0_30", "50_0_30", "100_0_60"]

worksheet.write_row("A1", col_name)
worksheet.write_column('A1', row_name)
worksheet.write_column('B2', data[0])
worksheet.write_column('C2', data[1])

# Configure the charts. In simplest case we just add some data series.
chart.add_series({'categories': '=Sheet1!$A$2:$A$6',
                  'values': '=Sheet1!$B$2:$B$11', "name": "10_0_30"})
chart.add_series({'values': '=Sheet1!$C$2:$C$11', "name": "50_0_30 (x10)"})
chart.add_series({'values': '=Sheet1!$D$2:$D$11', "name": "100_0_60 (x100)"})

# Insert the chart into the worksheet.
worksheet.insert_chart('F1', chart)

workbook.close()
