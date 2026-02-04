# def get_ids(count: int) -> List[int]:
#     # 


batched_ids = []
BATCH_SIZE = 100

def get_one_id():
    if len(batched_ids) == 0:
        batched_ids = get_ids(BATCH_SIZE)
    id = batched_ids[-1]
    batched_ids.pop()
    return id
