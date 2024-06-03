import requests, random
def fetch(url):
    response = requests.get(url)
    return response.json()
def seen_problems(user):
    user_results = f'https://codeforces.com/api/user.status?handle={user}&from=1&count=1000000'
    user_results = fetch(user_results)
    assert user_results['status'] == 'OK'
    problems = set()
    for submission in user_results['result']:
        problems.add(submission['problem']['name'])
    return (problems)
def rating(user):
    user_results = f'https://codeforces.com/api/user.info?handles={user}'
    user_results = fetch(user_results)
    assert user_results['status'] == 'OK'
    return user_results['result'][0]['rating']
problems = fetch('https://codeforces.com/api/problemset.problems')
player_1 = 'ssk4988'
player_2 = 'surajchip2'
rting = None
seen = seen_problems(player_1) | seen_problems(player_2)
print(f'you have seen {len(seen)} problems total')
if rting is None:
    rating_1 = rating(player_1)
    rating_2 = rating(player_2)
    rting = min(rating_1, rating_2)
    rting = min(rting - 400, rting // 2 + 300)
    # round to nearest 100
    rting = (rting + 50) // 100 * 100
print(f'chosen rating: {rting}')
good_problems = []
for t in problems['result']['problems']:
    if 'rating' not in t:
        continue
    if t['name'] not in seen and t['rating'] == rting and '*special' not in t['tags']:
        url = f'https://codeforces.com/problemset/problem/{t["contestId"]}/{t["index"]}'
        good_problems.append([t['name'],url])
random.shuffle(good_problems)
print('available problems:',len(good_problems))
for i in range(9):
    print(f'{i+1} ({i//3+1},{i%3+1})',*good_problems[i])
