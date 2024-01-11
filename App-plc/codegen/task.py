class Task:
    def __init__(self, task_id, vars, period, period_unit, priority):
        self.task_id = task_id
        self.vars = vars
        self.period = period
        self.period_unit = period_unit
        self.priority = priority

    def __repr__(self):
        return f"Task(task_id={self.task_id}, vars={self.vars}, period={self.period}, " \
               f"period_unit={self.period_unit}, priority={self.priority})"
