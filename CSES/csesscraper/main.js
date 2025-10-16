import { JSDOM } from 'jsdom';
const usersToID = {
    "brianush1": 159266,
    "tmarks39": 90843,
    "azure01": 163129,
    "Skuthuru": 3552,
    "enwask": 175446,
    "QuinnG": 54954,
    "morgulveil": 196782,
    "xylenox": 205559,
    "Alg01": 121995,
    "ssk4988": 55452,
    "BooleanCube": 76354,
    "Rzhek": 225590,
    "arundeegutla": 152547,
    "SeptaCube": 191297,
    "script-mouse": 275375,
    "cameroncuster": 72634,
    "lrvideckis2": 267257,
    "JJCUBER": 234339,
    "medbar": 69714,
    "tbcb": 200475,
    "hector04": 276863,
    "fulminata": 288654,
    "amy621": 240360,
    "oreinke": 295814,
    "soliveira27": 275481,
    "CR3YN": 307281,
    "jacksons": 330349,
    "tiffanym": 328560,
    "wyseguy421": 259302,
    "nyxbird": 222957,
    "million1321": 370227,
    "Rhygon1": 368114,
    "sidhys127": 373243
};
const cookie = '1e09365c45f08bb987acb2c8d8f1b6bb592a51ad';
const headers = {
    'Cookie': `PHPSESSID=${cookie}`
};
const IDToUsers = Object.fromEntries(Object.entries(usersToID).map(([k, v]) => [v, k]));
async function parseProblem(link) {
    const statLink = link.replace('task', 'stats');
    const statDocument = new JSDOM(await fetch(statLink, {
        headers
    }).then(res => res.text()));
    const tr_rows = Array.from(statDocument.window.document.getElementsByTagName('tr'));
    tr_rows.slice(3);
    const users = tr_rows.map(tr => {
        const userLink = tr.getElementsByTagName('a')[0]?.href;
        if (!userLink)
            return null;
        const userID = userLink.split('/').pop();
        return userID;
    }).filter(Boolean);
    const userList = [];
    users.forEach((id, i) => {
        if (!(id in IDToUsers))
            return;
        const username = IDToUsers[id];
        userList.push(`${username} - Rank ${(i % 5) + 1} in ${i >= 5 ? 'Shortest Code' : 'Fastest Code'}`);
    });
    return userList;
}
async function parseProblems() {
    const document = new JSDOM(await fetch('https://cses.fi/problemset/list/').then(res => res.text()));
    const problems = Array.from(document.window.document.getElementsByClassName('task'));
    // const promises = problems.map(async (problem) => )
    for (const problem of problems) {
        const link = 'https://cses.fi' + problem.children[0].href;
        const name = problem.children[0].innerHTML;
        const problemId = link.split('/').pop();
        const userList = await parseProblem(link);
        if (userList.length > 0) {
            console.log(`${problemId} - ${name}:`);
            for (const user of userList) {
                console.log('   ', user);
            }
        }
    }
}
parseProblems();
//# sourceMappingURL=main.js.map